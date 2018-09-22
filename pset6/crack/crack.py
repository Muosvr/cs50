import crypt

#password = input("Password: ")
hash_input = "50fkUxYHbnXGw"
#print(crypt.crypt(password, "50")== hash_input)

#generate full range of letters in a list

def checkPass(hash_input, genPass="A"):
    print(genPass)
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
            return checkPass(hash_input, genPass)
        elif lastLetter == "Z":
            numOfZs = genPass.count("Z")
            IdxBeforeZ = -(numOfZs + 1)
            if numOfZs == length:
                genPass = ""
                length += 1
            else:
                genPass = genPass[:IdxBeforeZ] + chr(ord(genPass[IdxBeforeZ]) + 1)

            for i in range(length-len(genPass)):
                genPass += "A"

        return checkPass(hash_input, genPass)




print(checkPass(hash_input))




