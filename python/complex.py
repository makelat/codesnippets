#Importing modules
#"np" is like an object that can be given vectors as arguments and it 
#performs varous operations on them, such as
#  np.dot(a,b)     
#  np.matmul(A,B)  matrix multiplication
import numpy as np
from numpy.linalg import inv
import cmath

#3D vectors
z1 = complex(1.,2.)
print 'z1= ',z1
print 'Re(z)= ',z1.real
print 'Im(z)= ',z1.imag

z2 = complex(3.,4.)
print 'z2= ',z2
print 'z1 + z2 = ', z1+z2
