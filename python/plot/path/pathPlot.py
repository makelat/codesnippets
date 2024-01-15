# importing the required modules
import matplotlib.pyplot as plt 
import numpy as np
import math

dt=0.01
Nt=100
xP=[]
yP=[]
R=1.
coef=2.*math.pi
for ti in range(Nt):
    t=dt*ti
    x=R*np.cos(coef*t)
    y=R*np.sin(coef*t)
    print '(x,y) = ('+str(x)+','+str(y)+')'
    xP.append(x)
    yP.append(y)

plt.plot([-1.1*R,1.1*R],[-1.1*R,1.1*R])  #"Limit setup graph"
plt.plot(xP,yP)
plt.xlabel(r'$x$ [m]') 
plt.ylabel(r'$y$ [m]') 
plt.savefig("pathPlot.pdf")
plt.clf()
