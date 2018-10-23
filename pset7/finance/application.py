import os
import datetime

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

class Stock:
    def __init__(self, owner, symbol):
        self.owner = owner
        self.symbol = symbol
        self.name = lookup(self.symbol)["name"]
        self.update()

    #to be tested
    def get_quantity(self):
        self.quantity = db.execute(
            "SELECT SUM(quantity) FROM history WHERE username=:username GROUP BY stock_symbol HAVING stock_symbol=:symbol",
            username = self.owner, symbol = self.symbol)[0]["SUM(quantity)"]

    def get_price(self):
        self.price = lookup(self.symbol)["price"]

    def update(self):
        self.get_price()
        self.get_quantity()
        self.total_value = usd(self.price * self.quantity)

@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    stocks = []
    username = session.get("username")
    symbol_list = db.execute("SELECT stock_symbol FROM history WHERE username=:username GROUP BY stock_symbol", username=username)
    cash_balance = db.execute("SELECT cash FROM users WHERE username=:username", username=username)[0]["cash"]
    total_value = cash_balance

    for sym in symbol_list:
        symbol = sym["stock_symbol"]
        new_stock = Stock(username, symbol)
        stocks.append(new_stock)
        total_value += new_stock.quantity * new_stock.price


    return render_template("portfolio.html", stocks = stocks, cash_balance=usd(cash_balance), total_value=usd(total_value))

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    username = session.get("username")
    # print(f'username: {username}')

    if request.method=="POST":
        symbol = request.form.get("symbol")
        quantity = request.form.get("quantity")
        if not quantity.isdigit() or int(quantity)<=0:
            return apology("Quantity must be a positive integer", 400)
        quantity = int(quantity)
        price = 0
        message = ""
        time = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        response = lookup(symbol)
        if not response:
            return apology("Invalid symbol", 400)

        price = response["price"]
        name = response["name"]
        cash = db.execute("SELECT cash FROM users WHERE username=:username", username=username)[0]["cash"]
        cost = price * float(quantity)
        status = "bought"
        if cash >= cost:
            cash -= cost
            db.execute("UPDATE users SET cash=:cash WHERE username=:username", cash=cash, username=username)
            db.execute("INSERT INTO history (username, stock_symbol, unit_price, time, quantity, stock_name, status) VALUES (:username, :stock_symbol, :unit_price, :time, :quantity, :name, :status)",
                        username = username, stock_symbol=symbol, unit_price=price, time=time, quantity=quantity, name=name, status=status)
            message = f'Recorded purchase {quantity} share(s) of {name} at ${price}/stock'
            return render_template("buy.html", message=message)
        else:
            return apology("Not enough cash", 400)
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    username = session.get("username")
    history=db.execute("SELECT stock_symbol, unit_price, time, quantity, stock_name, status FROM history WHERE username=:username",
                       username=username)
    return render_template("history.html", history=history)

@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]
        session["username"] = rows[0]["username"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    name = ""
    price = ""
    symbol = ""
    message = ""
    if request.method == "POST":
        response = lookup(request.form.get("symbol"))
        if response:
            name = response["name"]
            price = response["price"]
            symbol = response["symbol"]
            return render_template("quote.html", name=name, price=price, symbol=symbol)
        else:
            message = "Symbol not found!"
            return render_template("quote.html", name=name, price=price, symbol=symbol, message=message)
    else:
        return render_template("quote.html", name=name, price=price, symbol=symbol)


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    session.clear()

    if request.method == "POST":

        #check if username is blank
        if not request.form.get("username"):
            return apology("Please provide user name", 400)

        #check if password is blank
        if not request.form.get("password"):
            return apology("Please provide password", 400)

        #enter password again to confirm
        if not request.form.get("password") == request.form.get("confirmation"):
            return apology("Password does not match", 400)

        #check if user name already exist
        if db.execute("SELECT username from users WHERE username = :username",
                                        username=request.form.get("username")):
            return apology("Username already exist", 400)

        #generate password hash and get username
        hash = generate_password_hash(request.form.get("password"))
        username = request.form.get("username")


        #inser new user into database
        db.execute("INSERT INTO users (username, hash) VALUES (:username, :hash)",
                    username=username, hash = hash)
        message = "Please log in"
        return render_template("login.html", message=message)
        #TODO add redirect to success message

    else:
        return render_template("register.html")
@app.route("/add_cash", methods=["GET", "POST"])
@login_required
def add_cash():
    if request.method == "POST":
        username = session.get("username")
        add_cash = int(request.form.get("add_cash"))
        if add_cash <= 0:
            return apology("Cash amount must be positive integer", 400)
        db.execute("UPDATE users SET cash=cash+:add_cash WHERE username=:username",
                   add_cash=add_cash, username=username)
        flash(f"{add_cash} USD has been added to your account")
        return redirect("/")
    else:
        return render_template("portfolio.html")

@app.route("/change_pass", methods=["GET", "POST"])
@login_required
def change_pass():
    if request.method == "POST":
        username = session.get("username")
        hash = db.execute("SELECT hash FROM users WHERE username=:username", username=username)[0]["hash"]
        if not check_password_hash(hash, request.form.get("old_password")):
            return apology("Incorrect password", 403)
        if request.form.get("new_password") != request.form.get("confirmation"):
            return apology("Passwords do not match", 400)
        new_hash = generate_password_hash(request.form.get("new_password"))
        db.execute("UPDATE users SET hash=:new_hash WHERE username=:username", new_hash=new_hash, username=username)
        session.clear()
        flash("Password change successful! Please log in with new password.")
        return render_template("login.html")
    else:
        return render_template("ChangePass.html")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        req_quantity = request.form.get("shares")
        if not req_quantity.isdigit() or int(req_quantity)<=0:
            return apology("Quantity must be positive integer", 400)
        req_quantity = int(req_quantity)
        status = "sold"

        time = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")

        username = session.get("username")
        owned_stock = db.execute("SELECT SUM(quantity) FROM history WHERE username=:username GROUP BY stock_symbol HAVING stock_symbol=:symbol",
                                    username=username, symbol=symbol)
        if owned_stock:
            owned_quantity = owned_stock[0]["SUM(quantity)"]
            stock = lookup(symbol)
            price = stock["price"]
            name = stock["name"]
        else:
            owned_quantity = 0
        if owned_quantity>=req_quantity:
            total_value = req_quantity * price
            db.execute("INSERT INTO history (username, stock_symbol, unit_price, time, quantity, stock_name, status) VALUES (:username, :symbol, :price, :time, :quantity, :name, :status)",
                       username=username, symbol=symbol, price=price, time=time, quantity=-req_quantity, name=name, status=status)
            db.execute("UPDATE users SET cash = cash+:total_value WHERE username=:username",
                       total_value=total_value, username=username)
            message = f"Recorded sold {req_quantity} share(s) of {name} total ${total_value}"
            return render_template("sell.html", message = message)
        else:
            return apology("Insufficient shares", 400)
        # if db.execute()
    else:
        return render_template("sell.html")


def errorhandler(e):
    """Handle error"""
    return apology(e.name, e.code)


# listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
