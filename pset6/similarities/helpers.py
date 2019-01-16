import nltk
from nltk.tokenize import sent_tokenize

def lines(a, b):
    """Return lines in both a and b"""
    same = []
    uniq = []

    # split each string (a, b) into lines
    list_a = a.splitlines()
    list_b = b.splitlines()

    # get matches
    for line in list_a:
        if line in list_b:
            same.append(line)

    # remove duplicates
    for line in same:
        if line not in uniq:
            uniq.append(line)

    return uniq


def sentences(a, b):
    """Return sentences in both a and b"""
    same = []
    uniq = []

    # split each string (a, b) into sentences
    list_a = nltk.sent_tokenize(a, language='english')
    list_b = nltk.sent_tokenize(b, language='english')

    # get matches
    for sent in list_a:
        if sent in list_b:
            same.append(sent)

    # remove duplicates
    for sent in same:
        if sent not in uniq:
            uniq.append(sent)

    return uniq


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""
    same = []
    uniq = []

    # remove \n's from strings
    new_a = a.replace("\n", "")
    new_b = b.replace("\n", "")

    # split each string (a, b) into lines
    list_a = []
    list_b = []

    # Extract substrings from strings
    for s in range(len(new_a) - n + 1):
        list_a.append(new_a[s:s + n])

    for s in range(len(new_b) - n + 1):
        list_b.append(new_b[s:s + n])

    # get matches
    for sent in list_a:
        if sent in list_b:
            same.append(sent)

    # remove duplicates
    for sent in same:
        if sent not in uniq:
            uniq.append(sent)

    return uniq
