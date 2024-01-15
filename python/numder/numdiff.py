import numpy as np
import matplotlib.pyplot as plt

#Numerically solve diff. eq.:
#   - d^2 G / dr^2 = delta(r)   
#Recall that 2nd derivative is given by
#    (func(x+eps) - 2*func(x) + func(x-eps))/(eps)**2

#Potential
def V(r):
    return 1/(r+0.1)

#Spatial grid
ngrid = 100
r0, r1 = 0, 1
r = np.linspace(r0, r1, ngrid)

G = np.zeros(ngrid) #Init

#step size in numerical derivative
eps = 0.1

#Boundary condition
delta0 = 0
G[0] = delta0

#Deduce the second point from bd. cnd.
G[1] = -(delta0 + V(r[0]))*eps**2 + 2*G[0]

#The rest of the points can be found systematically
ind = range(ngrid-2)
for i in ind:
    G[i+2] = -(V(r[i+1]))*eps**2 + 2*G[i+1] - G[i]

#Plot, scale derivative values down for better illustration
plt.plot(r, G, 'o', color='k')
plt.xlabel(r'$r$')
plt.ylabel(r'$G(r)$')
plt.legend()
plt.savefig('numdiff.pdf')
