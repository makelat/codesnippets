#Example to illustrate fitting multiple functions at the same time, 
#using the same function / parameters, i.e. only one cost function is minimized
import matplotlib.pyplot as plt 
import numpy as np
from scipy.optimize import leastsq as lsq

#The function f(x) with fit parameters a and b, plus a given parameter C.
def function(x, a, b, C):
    return C*(a*x + b*x**2)

#Initial values for parameters a and b
a0=1
b0=1
params0 = [a0, b0]

#The ~cost function to be minimized, passed on to scipy least squares
def toMinimize(pars, *args):
    #Fetch parameters and arguments from input arrays
    a = pars[0]
    b = pars[1]
    x = args[0]
    y = args[1]
    C = args[2]
    n = args[3]    
    #Compute corresponding y values
    yfit = np.empty(x.shape)
    yfit[:n] = function(x[:n], a, b, C[0])
    yfit[n:] = function(x[n:], a, b, C[1])
    #Return difference between fit (iteration) and data
    return y - yfit

#Define two "datasets". The same functional form that will eventually be fitted is used,
#so the fit would naturally turn out very good. However, the point is that the two are 
#best described by slightly different values of a and b (at the same values of x) and
#the fit should converge into a compromise between the two

#Dataset 1
x1 = np.linspace(0,2,10)
y1 = [2.0*(0.2*x + 0.4*x**2) for x in x1]

#Dataset 2
x2 = np.linspace(0,2,10)
y2 = [3.0*(0.15*x + 0.45*x**2) for x in x2]

#Gather all x and y into single arrays
xall=np.append(x1,x2)
yall=np.append(y1,y2)

#The given parameters (not fitted), here e.g. normalization.
#For simplicity, these "Ansatz" values are exactly right -- the point is only
#to illustrate passing non-fit parameters
Carr = [2.0, 3.0]

Nx1 = len(x1)
args = (xall, yall, Carr, Nx1)

#Perform fit, fetch resulting fit parameter a and b values
result = lsq(toMinimize, params0, args=args)
print(result)
fitpars = result[0]
afit = fitpars[0]
bfit = fitpars[1]

#Plot data
plt.plot(x1,y1,marker='o',lw=0.,label=r'Dataset 1') 
plt.plot(x2,y2,marker='o',lw=0.,label=r'Dataset 2')
#Plot fits
xtmp=np.linspace(0,2,20)
plt.plot(xtmp,function(xtmp,afit,bfit,Carr[0]),label=r'Fit 1') 
plt.plot(xtmp,function(xtmp,afit,bfit,Carr[1]),label=r'Fit 2') 
#Titlesetup etc, save image
plt.title('Fit same parameters to 2 datasets at once')
plt.ylabel(r'$y$')
plt.xlabel(r'$x$') 
plt.legend(frameon=False)
plt.savefig('multifit.pdf')
plt.clf()
