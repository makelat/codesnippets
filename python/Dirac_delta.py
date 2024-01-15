# importing the required modules
import matplotlib.pyplot as plt 
import numpy as np

x = np.linspace(0,1,100)

#A simple function to be integrated over the range in x
def func(a):
    return a*a

#Dirac delta function
def Ddelta(a, tol):
    ret = 0
    if a < 0.5*tol and a > -0.5*tol:
        ret = 1./tol
    return ret

#Integration grid step size
w = x[1]-x[0]

#Dirac delta argument i.e. should evaluate function at x = Darg
Darg = 0.2

#Neglect last element (boundary 1) in integration
integral = 0
for a in x[:-1] :
    #integration
    integral += (x[1]-x[0])*func(a)
    print a, func(a), integral, Ddelta(Darg-a,w)

#Neglect last element (boundary 1) in integration
integral = 0
for a in x[:-1] :
    #integration
    integral += (x[1]-x[0])*func(a)*Ddelta(Darg-a,w)

print "\nTotal integral with Ddelta at",Darg,"=",integral 
