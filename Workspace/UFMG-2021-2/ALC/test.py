import numpy as np
from numpy import linalg as LA

w,v = LA.eig(np.diag((1,2,3)))
d = w*v
j = np.diag((1,2,3))
print(j)