from re import A
import numpy as np

def qrAlgorithm(A):
    A0 = A
    for i in range(10):
        q, r = np.linalg.qr(A0)
        A0 = q.T @ A0 @ q
    return(A0)

A = np.array([[1, 0, 1], [-1, 1, 0]])
S = A @ A.T
B = qrAlgorithm(S)
C = np.sqrt(B)
print(C)