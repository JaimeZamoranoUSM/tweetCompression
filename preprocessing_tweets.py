#RegExp for removing unnecesary data: (\w+,\w+,\d+-\d+-\d+ \d+:\d+:\d+,)
#RegExp for removing retweets: ((.)+RT (@\w+: ))
#RegExp for removing emojis: (\\x\w+)
#RegExp for removing special characters: (\\\w)
#RegExp for removing mentions: (@\w+)
#RegExp for removing hashtags: (#\w+)
#RegExp for removing links: (https:\/\/(www.)?\w+.\w+(\/\w+)?)
#RegExp to filter rest of the text ^b|([^A-Z|a-z| |,|.|;|:])
import re
import os

directory_in_str="/home/jaime/Escritorio/Universidad/Data"
directory = os.fsencode(directory_in_str)
ff = open("finalTweets.txt", "w")
lineset = set()
for file in os.listdir(directory):
    filename = os.fsdecode(file)
    print(filename)
    f = open(directory_in_str+"/"+filename, "r")
    for line in f:
        p = re.compile(r'(\w+,\w+,\d+-\d+-\d+ \d+:\d+:\d+,)')
        newA = p.sub("",line)
        #print(newA)
        q = re.compile(r'(\\x\w+)|(\\\w)')
        newB = q.sub("",newA)
        #print(newB)
        r = re.compile(r'(^.b|^b|"\\")')
        newC = r.sub("",newB)
        s = re.compile(r'((^ +)|( +$))|(( ){2,})')
        newD = s.sub("",newC)
        t = re.compile(r'( )')
        check = t.sub("",newD)
        if (check != ""):
            #print(newC)
            lineset.add(newD)
        #for match in cond:
        #    m = match.span()
        #    print(m)
    f.close()
linesCount=len(lineset)
ff.write(str(linesCount)+"\n")
n=0
for line in lineset:
    n+=1
    print("writing "+str(n)+" / "+str(linesCount))
    ff.write(line)
ff.close()
