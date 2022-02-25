def euclides(a,b):
    if(b == 0):
        return a
    r = a % b
    return euclides(b,r)

def exteuclides(a,b):
    if b == 0:
        return (a,1,0)
    else:
        r = a % b
        q = (a - r)/b
        (g,x,y) = exteuclides(b,r)

    return (g,y,x-q*y)


#x = int(input("x = "))
#y = int(input("y = "))


primos = []
for i in range(0, 12):
    m = euclides(i, 12)
    if(m == 1):
        print(i)

print(euclides(0, 12))