import crypt

#password = input("Password: ")
hash_input = str(input("Please enter hash: "))

if hash_input == "" or len(hash_input.split(" ")) > 1:
    print("Invalid hash input")
#print(crypt.crypt(password, "50")== hash_input)

#generate full range of letters in a list

def checkPass(hash_input, genPass="A"):
    while(True):
        if crypt.crypt(genPass, "50") == hash_input:
            return genPass
        elif crypt.crypt(genPass.lower(),"50") == hash_input:
            return genPass.lower()
        elif len(genPass) > 5:
            return "Password not found"
        else:
            length = len(genPass)
            lastLetter = genPass[length-1]

            if lastLetter != "Z":
                genPass = genPass[:length-1] + chr(ord(lastLetter)+1)

            elif lastLetter == "Z":
                numOfZs = 0
                for i in reversed(genPass):
                    if i == "Z":
                        numOfZs += 1
                    else:
                        break

                IdxBeforeZ = -(numOfZs + 1)

                if numOfZs == length:
                    genPass = ""
                    length += 1
                else:
                    genPass = genPass[:IdxBeforeZ] + chr(ord(genPass[IdxBeforeZ]) + 1)

                for i in range(length-len(genPass)):
                    genPass += "A"


print(checkPass(hash_input))




