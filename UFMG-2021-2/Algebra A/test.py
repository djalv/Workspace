import math

def crivo(M):
    primo = [True] * M

    primo[0], primo[1] = False, False

    for i in range(2,math.floor(math.sqrt(M))+1):
        if primo[i]:
            j = i*i
            while(j <= M):
                primo[j] = False
                j += i
    return primo

def euclides(a,b):
    if(b == 0):
        return a
    r = a % b
    return euclides(b,r)

primos = []
k = 0
for l in crivo(211):
    if l:
        primos.append(k)
    k = k + 1

for i in primos:
    if(euclides(i,211) == 1):
        print(i)