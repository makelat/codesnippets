# importing the required modules
import matplotlib.pyplot as plt 
import numpy as np

N=100
x=np.linspace(0,1,N)
f1=np.linspace(100,10,N)
f2 = np.multiply(2,f1)
f3 = np.sum([f1,np.multiply(10,np.ones(N))],axis=0)

# plotting the points  
plt.plot(x, f1, label=r'f(x)') 
plt.plot(x, f2, label=r'2f(x)') 
plt.plot(x, f3, label=r'f(x)+10') 
plt.yscale("log")
plt.ylabel(r'x') 
plt.xlabel(r'f') 
plt.legend()

plt.savefig("factorInLogDependence.pdf")
plt.clf()
