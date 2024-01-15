#Adapted from C. Hill "Learning Scientific Programming With Python"
#Works with Python 2.7, but requires scipy > 0.19.1
#Run by
#    python harm_osc.py

import numpy as np
from scipy.integrate import solve_ivp
import matplotlib.pyplot as plt

#Harmonic oscillator frequency (s-1)
omega = 0.9
#Initial conditions on x1 = x and x2 = dx/dt at t = 0
A, v0 = 3, 0    #cm, cm/s
x0 = A, v0

#Grid of time points
t0, tf = 0, 20

#m d^2x/dt^2 = - x k
#d^2x/dt^2 = - x k/m    | omega = sqrt(k/m)
#d^2x/dt^2 = - x omega**2
def dxdt(t, x):
    #Return dx/dt = f(t, x) at time t
    x1, x2 = x
    dx1dt = x2
    dx2dt = -omega**2 * x1
    return dx1dt, dx2dt

#Integrate the differential equation
soln = solve_ivp(dxdt, (t0, tf), x0, dense_output=True)

t = np.linspace(t0, tf, 100)
x1, x2 = soln.sol(t)

#Plot and compare the numerical and exact solutions
plt.plot(t, x1, 'o', color='k', label=r'solve_ivp()')
plt.plot(t, A * np.cos(omega * t), color='gray', label='Exact')
plt.xlabel(r'$t\;[\mathrm{s}]$')
plt.ylabel(r'$x\;[\mathrm{cm}]$')
plt.legend()
#plt.show()
plt.savefig('harm_osc.pdf')
