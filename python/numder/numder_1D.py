import numpy as np
import matplotlib.pyplot as plt

#Function to differentiate. Input arg can be a number or a vector
def f(x):
    a, b = -1, 0.25
    return a*x**2 + b*x**4

#1st derivative (numerically)
def der1(func,x):
    delta = 0.1
    return (func(x+delta) - func(x-delta))/(2*delta)

#2nd derivative (numerically)
def der2(func,x):
    delta = 0.1
    return (func(x+delta) - 2*func(x) + func(x-delta))/(delta)**2

#Spatial grid
x0, x1 = 0, 2
x = np.linspace(x0, x1, 100)

fx        = f(x)           #Function value
dfxdx     = der1(f,x)      #1st derivative
d2fxdx2   = der2(f,x)      #2nd derivative
d2fxdx2_2 = der1(f,dfxdx)  #Agrees w/^ to a good approximation

#Plot, scale derivative values down for better illustration
plt.plot(x, fx,             'o', color='k', label=r'Function')
plt.plot(x, 0.1*dfxdx,      'o', color='r', label=r'1st der.($\times 0.1$)')
plt.plot(x, 0.01*d2fxdx2,   'o', color='b',
         label=r'2nd der.($\times 0.01$)')
plt.plot(x, 0.01*d2fxdx2+0.1, 'o', color='g',
         label=r'2nd der. approx.($\times0.01+0.1$)')
plt.xlabel(r'$x$')
plt.ylabel(r'$f, \frac{df}{dx}$')
plt.legend()
plt.savefig('numder_1D.pdf')
