def digitos(n, B):
    d = []
    while n > 0:
        r = n % B # n = qB+r com 0 <= r < B
        q = n // B
        d.insert(0, r)
        n = q
    return d

print(digitos(7760993,256))