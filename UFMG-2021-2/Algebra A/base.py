def digitos(a, B):
    d = []
    while a > 0:
        r = a % B # a = qB+r com 0 <= r < B
        q = a // B
        d.insert(0, r)
        a = q
    return d

print(digitos(7760993,256))