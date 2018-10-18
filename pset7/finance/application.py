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

@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    return apology("TODO")

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    username = session.get("username")
    # print(f'username: {username}')

    if request.method=="POST":
        symbol = request.form.get("symbol")
        quantity = request.form.get("quantity")
        price = 0
        message = ""
        time = datetime.datetime.now()
        response = lookup(symbol)

        if response:
            price = response["price"]
            name = response["name"]
            db.execute("INSERT INTO history (username, stock_symbol, unit_price, time, quantity) VALUES (:username, :stock_symbol, :unit_price, :time, :quantity)",
                        username = username, stock_symbol=symbol, unit_price=price, time=time, quantity=quantity)
            message = f'Recorded purchase {quantity} stock(s) of {name} on {time.strftime("%c")}'
            return render_template("buy.html", message=message)
        else:
            message = "Invalid symbol"
            return render_template("buy.html", message=message)
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    return apology("TODO")

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
            return apology("Please provide user name", 403)

        #check if password is blank
        if not request.form.get("password"):
            return apology("Please provide password", 403)

        #enter password again to confirm
        if not request.form.get("password") == request.form.get("confirmation"):
            return apology("Password does not match", 403)

        #check if user name already exist
        if db.execute("SELECT username from users WHERE username = :username",
                                        username=request.form.get("username")):
            return apology("Username already exist", 403)

        #generate password hash and get username
        hash = generate_password_hash(request.form.get("password"))
        username = request.form.get("username")


        #inser new user into database
        db.execute("INSERT INTO users (username, hash) VALUES (:username, :hash)",
                    username=username, hash = hash)
        return redirect("/")
        #TODO add redirect to success message

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    return apology("TODO")


def errorhandler(e):
    """Handle error"""
    return apology(e.name, e.code)


# listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
