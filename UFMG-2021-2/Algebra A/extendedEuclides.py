def euclides(a,b):
    if b == 0:
        return (a,1,0)
    else:
        r = a % b
        q = (a - r)/b
        (g,x,y) = euclides(b,r)

    return (g,y,x-q*y)

print(euclides(42,27))