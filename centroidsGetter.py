f = open("out5.txt","r")
pos=0
cant=7894
centroides=[]
for line in f:
    if pos>cant:
        break
    if pos>0:
        centroides.append(int(line))
    pos+=1
centroides.sort()
for centroide in centroides:
    centroide-=1
    print(centroide)


og = open("train.txt","r")
nuevo = open("centroidsP5R.txt","w")
pos=0
used=0
nuevo.write(str(len(centroides))+"\n")
for linea in og:
    if(pos in centroides):
        used+=1
        if used==len(centroides):
            nuevo.write(linea.rstrip())
            break
        else:
            nuevo.write(linea)
    pos+=1
f.close()
og.close()
nuevo.close()
