import numpy as np

def SVD(A):
    U, sigma, Vt = np.linalg.svd(A)
    return U, sigma, Vt


A = np.array([[3, 2], [2, 3], [2, -2]])

U, sigma, Vt = SVD(A)

print(f'{U} \n {sigma} \n {Vt} \n')
