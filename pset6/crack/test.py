print(chr(65))
input = "APPLE"
print(input.lower())
print(input[len(input)-1])
print("Ascii number of A: ", ord("A"))
print("Next letter of A: ", chr(ord("A")+1))
print("input == APPLE: ", input == "APPLE")

def check (num1, num2 = 3):
    print("num1: ", num1)
    print("num2: ", num2)

check(4)
check(4, 5)

input = input[:len(input)-1]

print("Get rid of last letter", input)
print("Z in AAZZZ", "AAZZZ".count("Z"))
print("Get rid of Zs at the end", "AAZZZ"[:-3])
print("Letter before Z: ", "ABCZZZ"[-4])
