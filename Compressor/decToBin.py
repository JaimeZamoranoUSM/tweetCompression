def listToString(s):

    # initialize an empty string
    str1 = ""

    # traverse in the string
    for ele in s:
        str1 += ele

    # return string
    return str1

def dec_to_bin(x):
    return bin(x)[2:]

arch = open("decValues","r")
text=""
for numbers in arch:
    final=list(dec_to_bin(int(numbers)))
    while(len(final)<8):
        final.insert(0,'0')
    text+=listToString(final)
print(text)
