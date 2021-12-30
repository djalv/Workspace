import numpy as np

def powerMethod(A, niter=10):
    n = len(A)
    w = np.ones((n,1))/n
    for i in range(niter):
        w = A.dot(w)        
    return w

def matrizDeTransicao(A):
    x = np.sum(A, 1)
    D = np.transpose(np.transpose(A)*(1/x))
    
    return D

def powerMethodEps(A, epsilon):
    n = len(A)
    w0 = np.zeros((n,1))
    w1 = np.ones((n,1))/n
    iters = 0
    while(np.linalg.norm(w0-w1) >= epsilon):
        w0 = w1
        w1 = A.dot(w1)
        iters = iters + 1
    return w1,iters

A = np.array([[0,0,0,1],[1,0,0,1],[1,1,0,1],[0,1,1,0]])

P = matrizDeTransicao(A)
PT = np.transpose(P)

l,x = np.linalg.eig(PT)

autovec = (1/sum(x[:,0])) * x[:,0]
print(autovec)

result_pm = powerMethod(PT)
print(result_pm)

result_pm_eps, nb_iters = powerMethodEps(PT, 10**-5)
print(result_pm_eps, nb_iters)