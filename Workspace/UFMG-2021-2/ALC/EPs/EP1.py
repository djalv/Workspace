import numpy as np
import matplotlib.pyplot as plt
import random as rnd
"""
Questão 1
a = np.matrix([[2,1,3],[3,1,4],[5,7,12]])
b = np.matrix([[1,0,0], [0,1,0], [0,0,1]])
c = np.matrix([[3],[1],[2]])

aT = np.transpose(a)

d = a*b
e = aT + b
f = a*c

Questão 2
dados = np.array([[3.4,4.4], [0.6,3.7],
                 [4.2,3.8], [-0.1,3.8],
                 [1.2,3.8],[3.2,3.2],
                 [3.9,2.3],[1.4,3.6],
                 [3.6,4.7],[1.0,3.6]])

a = np.array([6,9])
novos_dados = dados + a

plt.scatter(dados[:,0],dados[:,1])
plt.scatter(novos_dados[:,0], novos_dados[:,1])
plt.show()
"""

cont = 1

G = np.matrix([[3,6,9],[5,10,15]])

cont = 10
while(cont != 0):    
    x = np.array([[rnd.randrange(-10, 11, 1)],[rnd.randrange(-10, 11, 1)],[rnd.randrange(-10, 11, 1)]])
    y = G*x
    
    plt.scatter(y.flat[0], y.flat[1])

    cont = cont - 1


plt.show()