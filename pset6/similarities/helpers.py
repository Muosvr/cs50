from nltk.tokenize import sent_tokenize

def lines(a, b):
    """Return lines in both a and b"""
    list_a = a.split('\n')
    list_b = b.split('\n')

    sim = []
    for line in list_a:
        if line in list_b:
            if line not in sim:
                sim.append(line)
    print(sim)
    return sim

def sentences(a, b):
    """Return sentences in both a and b"""
    #Need to use tokenization
    list_a = sent_tokenize(a)
    list_b = sent_tokenize(b)

    sim = []
    for sent in list_a:
        if sent in list_b and sent not in sim:
            sim.append(sent)
    print(sim)
    return sim

def substrings(a, b, n):
    """Return substrings of length n in both a and b"""
    shorterStr = a if len(a)<=len(b) else b

    sim = []
    for i in range(len(a)-n+1):
        subStr = a[i:i+n]
        if subStr in b and subStr not in sim:
            sim.append(subStr)
    return sim
