from cmath import sqrt
import numpy as np

father = np.array([-0.5, 0.87])
mother = np.array([-1, 0])
g = np.array([-0.71, 0.71])


u = (mother + father)/2

ub = np.inner(u, g) * g
y = u - ub

z = sqrt(1 - ((np.linalg.norm(y))**2))
Va = y - z*g
print(z*g)
