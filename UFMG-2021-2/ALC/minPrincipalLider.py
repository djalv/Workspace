import numpy as np

def min_main_leader(S):
    det = []
    n = np.shape(A)
    for i in range(1,n[0]+1):
        x = np.linalg.det(S[:i,:i])
        det.append(x)
    return det

A = np.array([[3,4], [4,5]])
print(min_main_leader(A))