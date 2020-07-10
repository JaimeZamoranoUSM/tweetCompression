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
for file in os.listdir(directory):
    filename = os.fsdecode(file)
    print(filename)
    f = open(directory_in_str+"/"+filename, "r")
    for line in f:
        p = re.compile(r'(\w+,\w+,\d+-\d+-\d+ \d+:\d+:\d+,)')
        string=''' "b""Superstar commentators @beemerpga and @Luke_Elvy are coming to #PGATOUR2K21... and they're gonna have a LOT to say\xe2\x80\xa6 https://t.co/KMvQwcyZQP""" '''
        cond = p.finditer(string)
        newA = p.sub("",line)
        #print(newA)
        q = re.compile(r'(^ |((.)+RT (@\w+: ))|(\\x\w+)|(\\\w)|(@\w+)|(#\w+)|(https:\/\/(www.)?\w+.\w+(\/\w+)?))')
        newB = q.sub("",newA)
        #print(newB)
        r = re.compile(r'(^b|([^A-Z|a-z| |,|.|;|:|\d]))')
        newC = r.sub("",newB)
        newC = r.sub("",newC)
        #print(newC)
        ff.write(newC+"\n")
        #for match in cond:
        #    m = match.span()
        #    print(m)
    f.close()
ff.close()
