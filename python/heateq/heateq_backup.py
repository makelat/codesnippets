import numpy as np
import matplotlib.pyplot as plt
import math

#Spatial and temporal grids
x0, t0 = 0., 0.
xf, tf = 3.*math.pi, 10.
nx, nt = 30, 30
dx = (xf-x0)/float(nx)
dt = (tf-t0)/float(nt)
t = np.linspace(t0, tf, nt)
x = np.linspace(x0, xf, nx)

#Store function values to matrix, introduce boundary conditions
f = np.zeros((nt,nx))

###Case 1: initially non-uniform heat profile dissipates over time
f[0,:] = np.sin(x)

###Case 2: heating at a point as a function of time
#f[0,:]    = 0          #Beginning: the whole rod is cold
#f[:,nx-1] = 0          #One end of the rod is always cold
#f[:,0]    = np.sin(t)  #Other end heated and cooled in waves

#Heat eq. is of the form:
#    d/dt u[t, x] == d^2/dx^2 u[t, x]
#Numerically:
#    (f(t+dt,x) - f(t,x))/dt = (f(t,x+dx) - 2*f(t,x) + f(t,x-dx))/(dx*dx)
#If t<0 or x<0, f=0.

#Deduce first x-line of non-assigned points:
#    (f(t[1],x[ix]))/(2*dt) = (f(t[0],x[ix+1]) - 2*f(t[0],x[ix]))/(dx*dx)
#        => f(t[1],x[ix])=0 for ix>0; recall f(t[1],x[0])=np.sin(t[1])
#for ix in range(nx-1): #NB this is correct but redundant due to zeros init
#    f[1,ix+1]=0        #NB this is correct but redundant due to zeros init

#For the rest, use the full formula in the form:
#    f(t+dt,x) = f(t,x) + dt*(f(t,x+dx) - 2*f(t,x) + f(t,x-dx))/(dx*dx)
#This part solves:
# xxxxx
#  xxx
#   x
for it in range(nt-1):
    for ix in range(it+1,nx-1-it):
        f[it+1,ix] = f[it,ix] + (f[it,ix+1]-2.*f[it,ix]+f[it,ix-1])*dt/(dx*dx)

#TODO rest of the solution

#Plot
im = plt.imshow(f, cmap='hot')
plt.colorbar(im, orientation='horizontal')
plt.savefig('heateq.pdf')
