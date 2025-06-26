import numpy as np
import random

#A matrix is singular if its determinant is zero or incalculable
def checkSingularity(A):
  try:
    det = np.linalg.det(A)
    return np.isclose(det, 0.)
  except np.linalg.LinAlgError:
    print('Cannot compute determinant')
    return True  # Matrix is singular if determinant cannot be calculated

#Init random matrix, expect not to be a linear combination of one another
N=3
A=[]
for _ in range(N): A.append([random.random() for _ in range(N)])

print('A random matrix\n',np.matrix(A))
print("is singular:",checkSingularity(A),' (not expected to be)')

#Now construct a matrix with off-diag entries constructed out of diag entries
B= [[np.sqrt(A[i][i]*A[j][j]) for j in range(len(A[i]))] for i in range(len(A))]
print('\nMatrix w/ off-diag entries constructed out of diag\n',np.matrix(B))
print("is singular:",checkSingularity(B),' (expected o be)')

#Check what happens if B diagonal is made equal to 1
for i in range(len(B)): B[i][i] = 1
print('\nMatrix\n',np.matrix(B))
print("is singular:",checkSingularity(B),' (not expected to be)')

#Construct a matrix out of two vectors r1,r2 s.t. there are the submatrices
#[[r1 x r1], [r1 x r2]; [r2 x r1], [r2, r2]]
r1 = [random.random() for _ in range(N)]
r2 = [random.random() for _ in range(N)]
C=[]
for r in [r1,r2]:
    for i in range(len(r)): C.append(np.multiply(r[i],r1+r2).tolist())
print('\nMatrix consructed out of submatrices, all from 2 vectors\n',C)
print("is singular:",checkSingularity(C),' (expected to be)')

#Again, check what happens if diagonal entries are made 1
for i in range(len(C)): C[i][i] = 1
print('\nMatrix as above, but diagonal 1\n',np.matrix(C))
print("is singular:",checkSingularity(C),' (not expected to be)')

#How about a triangular matrix?
for i in range(1,len(C)):
    for j in range(i): C[i][j] = 0
print('\nUpper triangle of above matrix\n',np.matrix(C))
print("is singular:",checkSingularity(C),' (not expected to be)')
