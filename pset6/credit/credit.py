def checkCardNum(number):
    number = list(map(int, number))
    length = len(number)
    numSum = 0

    for i in range(length-2, -1, -2):
        numSum += sum(list(map(int, str(number[i]*2))))

    for i in range(length-1, -1, -2):
        numSum += number[i]

    if numSum % 10 == 0:
        if number[0] == 4 and length in [13, 16]:
            print("VISA")
            return 0
        elif number[0] == 5 and number[1] in [1, 2, 3, 4, 5] and length == 16:
            print("MASTERCARD")
        elif number[0] == 3 and number[1] in [4, 7] and length == 15:
            print("AMEX")
            return 0

    print("INVALID")
    return 0

if __name__ == "__main__":

    while(True):
        n = input("Please enter a credit card number: ")
        if n.isnumeric():
            break

    checkCardNum(n)