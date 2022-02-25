import math

def coeficientes(n):
    q = n
    while(q % 2 == 0):
        q = q//2
    t = int(math.log2(n//q))
    return t, q

def miller(a, n):
    t, q = coeficientes(n-1)
    
    r = (a**q) % n
    
    if r % n == 1:
        return "Inconclusivo"
    
    for i in range(0,t):
        
        if r % n == (n-1):
            return "Inconclusivo"
        r = (r*r) % n
        
    
    return "Composto"
n = 561
print(coeficientes(n-1))
print(miller(2, n))