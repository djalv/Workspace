import math

def crivo(M):
    primo = [True] * M

    primo[0], primo[1] = False, False

    for i in range(2,math.floor(math.sqrt(M))+1):
        if primo[i]:
            j = i*i
            while(j < M):
                primo[j] = False
                j += i
    return primo

file = open('primes.txt', 'w')

primos = []
k = 0
for l in crivo(1000000):
    if l:
        file.writelines(f"{k}\n")
    k = k + 1
