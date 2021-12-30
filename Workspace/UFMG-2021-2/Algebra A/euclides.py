def euclides(a,b):
    if(b == 0):
        return a
    r = a % b
    return euclides(b,r)

x = int(input("x = "))
y = int(input("y = "))

print(euclides(x,y))
