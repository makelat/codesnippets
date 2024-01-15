# importing the required modules
import matplotlib.pyplot as plt 
import numpy as np

zrange = np.linspace(0,1,1000)

#The function for which the + distribution is to be found
def func(z):
    return np.log(1-z)/(1-z)

#Arbitrary test function, regular at z=1
def testf(z):
    return z


#Integration grid step size
dz = zrange[1]-zrange[0]

#Dirac delta argument i.e. should evaluate function at x = Darg
Darg = 0.2

#Neglect last element (boundary 1) in integration
integral = 0
for z in zrange[:-1] :
    #integration
    integral += (testf(z)-testf(1))*func(z)*dz
    print(z, func(z), integral)
print("^ z,              "+\
      "^ func(z),         "+\
      "^ acc. integral of plus(func(z))")
print("Last line & col to be compared with exact integral, yielding 1.")
print("C.f. Mathematica notebook")
