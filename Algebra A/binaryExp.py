def bin_exp(b, e, n):
    resp = 1
    pot_atual = b
    while e > 0:
        if e % 2 == 1:
            resp = (resp * pot_atual) % n
        pot_atual = (pot_atual**2) % n
        e = e // 2
    return resp

print(bin_exp(5, 110, 131))
    