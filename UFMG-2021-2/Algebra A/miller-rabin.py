import math
import random as rnd

def coeficientes(n):
    q = n
    while(q % 2 == 0):
        q = q//2
    t = int(math.log2(n//q))
    return t, q

def miller(a, n):
    t, q = coeficientes(n-1)
    
    r = (a**q) % n
    print(r);

    if r % n == 1:
        return "Inconclusivo"
    
    for i in range(0,t):
        
        if r % n == (n-1):
            return "Inconclusivo"
        r = (r*r) % n
        
    
    return "Composto"

def millerRabin(n, k):
    for i in range(k):
        a = rnd.randint(2,n-2)

        if miller(a, n) == "Composto":
            return "Composto"
    return "Provavelmente primo"

