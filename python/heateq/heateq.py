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
#For most points, use the formula in the form:
#    f(t+dt,x) = f(t,x) + dt*(f(t,x+dx) - 2*f(t,x) + f(t,x-dx))/(dx*dx)
for it in range(5):  #range(nt-1):
    for ix in range(1,nx-1):
        #All middle points
        f[it+1,ix] = f[it,ix] + f[it,ix+1]*dt/(dx*dx) - 2.*f[it,ix]*dt/(dx*dx) + f[it,ix-1]*dt/(dx*dx)
    #Low-x edge
#    f[it+1,0] = f[it+1,1]*dx*dx/dt - f[it,1]*dx*dx/dt + 2.*f[it+1,1] - f[it+1,2]
    #High-x edge
#    f[it+1,nx-1] = f[it+1,nx-2]*dx*dx/dt - f[it,nx-2]*dx*dx/dt + 2.*f[it+1,nx-2] - f[it+1,nx-3]

#Plot
im = plt.imshow(f, cmap='hot')
plt.colorbar(im, orientation='horizontal')
plt.savefig('heateq.pdf')
