import math

def fatoracao_prima(n):
    fatores = []

    for i in range(2, math.floor(math.sqrt(n))+1):
        while(n % i == 0):
            fatores.append(i)
            n = n // i
    if n > 1:
        fatores.append(n)
    return fatores

x = int(input("x = "))
print(fatoracao_prima(x))