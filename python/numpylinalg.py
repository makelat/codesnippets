#Importing modules
#"np" is like an object that can be given vectors as arguments and it 
#performs varous operations on them, such as
#  np.dot(a,b)     
#  np.matmul(A,B)  matrix multiplication
import numpy as np
from numpy.linalg import inv

#3D vectors
v1=[1,2,3]
v2=[4,5,6]
print '3D vectors v1 and v2: ',v1,v2 #both ' and " are ok for string

print 'Sum of all elements in v1 : ',np.sum(v1)

#Sum vector components, return a new vector
#First you need to put the vectors into a matrix and then sum inside the matrix. #'axis' specifies direction of summation: down (axis=0) or to the left (1) in
#  v1_0  v1_1  v1_2
#  v2_0  v2_1  v2_2
print 'v1+v2 componentwise, ax 0:', np.sum([v1, v2],axis=0)
print 'v1+v2 componentwise, ax 1:', np.sum([v1, v2],axis=1)

print 'v1*v2 componentwise:', np.multiply([v1, v2],axis=0).tolist()
print 'v1/v2 componentwise:', np.divide([v1, v2],axis=0).tolist()

#Operations that result in higher dim. vectors
v6D=v1+v2    #Returns a 6D vector
print "\n6D vector v6D: ", v6D
print 'Kroenecker product of v1 & v2, a 9D vector: ',np.kron(v1,v2)

#dot product included in numpy.linalg
vdot=np.dot(v1,v2)
print 'v1 v2 dot product=',vdot

#Outer product, turn v1 and v2 into a matrix
M1=np.outer(v1,v2)
print '\nOuter product of v1 & v2:'
print M1

#Imports need not always be done at start, only before you need them
import numpy.linalg as lin
#now you can call all functions included in numpy.linalg by either
#  numpy.linalg.function() OR lin.function()

#Matrix examples
A=[[1,2],[3,4]]
print '\n2x2 matrix A:\n', A
print 'np.det(A)=', lin.det(A)
#eig returns eigenvalues and -vectors
print 'A eigenvalues',np.linalg.eig(A)[0]
print 'A eigenvectors: '
for ev in lin.eig(A)[1]:  #no brackets, stop intendation where loop ends
    print ev

Ainv = inv(A)
print 'Inverse of A:\n', Ainv

print 'Check: A*Ainv=\n',np.matmul(Ainv,A)
