f = open("out.txt","r")
pos=0
cant=2035
centroides=set()
for line in f:
    if pos>0:
        if pos<cant+1:
            centroides.add(int(line))
    pos+=1
centroides=list(centroides)
centroides.sort()
for centroide in centroides:
    print(centroide)


og = open("trainee.txt","r")
nuevo = open("centroids.txt","w")
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
