from nltk.tokenize import sent_tokenize

def lines(a, b):
    """Return lines in both a and b"""
    list_a = [line.strip() for line in a.split('\n')]
    list_b = [line.strip() for line in b.split('\n')]

    sim = []
    for line in list_a:
        if line in list_b:
            if line not in sim:
                sim.append(line)
    # TODO
    # print(sim)
    return sim

# lines("Apple is on the tree.\nTree is green.\nThere are apple's on the tree", "Tree is green.\nApple is on the tree.\nThere are")

def sentences(a, b):
    """Return sentences in both a and b"""
    #Need to use tokenization
    list_a = [sent.strip() for sent in a.split(".")]
    list_b = [sent.strip() for sent in b.split(".")]

    sim = []
    for sent in list_a:
        if sent in list_b and sent not in sim:
            sim.append(sent)
    # TODO
    # print(sim)
    # print("This sentence is striped ".strip()+"###")
    return sim
# sentences("Apple is on the tree. It is green. It is green.","People are around the tree. It is green. There are apples on it")

def substrings(a, b, n):
    """Return substrings of length n in both a and b"""
    shorterStr = a if len(a)<=len(b) else b

    sim = []
    for i in range(len(shorterStr)):
        subStr = a[i:i+n]
        if subStr in b and subStr not in sim:
            sim.append(subStr)
    # TODO
    # print(sim)
    return sim

# substrings("Apple is on the tree. It is gree. It is green", "People are climbing on the apple tree. It is green and there are apples on it", 4)
