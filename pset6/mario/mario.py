def mario():
    n = 0
    while(True):
        n = input("Please enter the height between 1 and 23: ")
        if n.isnumeric():
            n = int(n)
            if n <= 23 and n >= 0:
                break
    for i in range(n-1, -1, -1):
        for j in range(i):
            print(" ", end="")
        for k in range((n-i)*2+2):
            if k == (n-i) or k == (n-i)+1:
                print(" ", end="")
            else:
                print("#", end="")

        print("")

if __name__=="__main__":
    mario()

