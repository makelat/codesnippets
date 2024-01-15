import numpy as np
import matplotlib.pyplot as plt
import cmath

#Constants
CF = 4./3.
CA = 3.
TF = 0.5
nf = 5
a1 = CA*31./9. - TF*nf*20./9.
gamE = 0.5772
beta0 = 0.25*(11./3.*CA - 2./3.*nf)
C18 = CF           #Singlet
#C18 = CF - 0.5*CA    #Octet

#Init
alpS = 0.2    #FIXME alpha_S(mu_B)
M    = 340.   #TODO should eventually take over a range of values
mt   = 172.4  #Kiyo-Moch
Gam  = 1.36   #Kiyo-Moch
mub  = 20.    #Hagiwara-Sumino-Yokoya

#Potential FIXME
def V(r):
    lg = np.log(mub*r)
    ret = -4.*np.pi*alpS*C18/r**2
    ret *= (1. + 0.25*alpS/np.pi*(2.*beta0*(lg + gamE) + a1))
    return complex(ret,0)

#Spatial grid
ngrid = 100
r0, r1 = 0., 1.  #FIXME dummy endpoint
r = np.linspace(r0, r1, ngrid)

G = np.zeros(ngrid, dtype=complex) #Init

#step size in numerical derivative
eps = 1./ngrid
eps2 = eps**2

#Dirac delta function
def Ddelta(a):
    ret = 0
    tol = eps
    if a < 0.5*tol and a > -0.5*tol:
        ret = 1./tol
    return ret

#Bd. cond., set wavefunction value away from origin
G[ngrid-1] = complex(1e-36,1e-36) #TODO

#Point 2nd closest to bd. is a special case
Hkin = complex(M - 2.*mt, Gam) + V(r[ngrid-1])
G[ngrid-2] = -G[ngrid-1]*eps2*Hkin + 2.*G[ngrid-1]

#The rest of the points can be found systematically
for i in range(ngrid-2):
    j = ngrid-3-i
    Hkin = complex(M - 2.*mt, Gam) + V(r[j+1])
    G[j]  = -G[j+1]*eps2*Hkin + 2.*G[j+1] + G[j+2] + Ddelta(r[j+1])
    #TODO Ddelta(r[j+1]) or Ddelta(r[j])?

#Plot, scale derivative values down for better illustration
plt.plot(r, G.imag, 'o', color='g')
#plt.plot(r, G.real, 'o', color='k')
plt.xlabel(r'$r$')
plt.ylabel(r'$ImG(r)$')
plt.savefig('numdiff_complex.pdf')
