#A script to illustrate multivariate interpolation. 
#Here a fine grid corresponding to a smooth surface in 3D space is scaled down,
#and a coarse surface is formed using linear interpolation on a low-resolution grid.
from mpl_toolkits.mplot3d import axes3d
from scipy.interpolate import LinearNDInterpolator
import numpy as np
import matplotlib.pyplot as plt

xlim=[-2,2]
ylim=[-3,3]

### Build fine grid
d=0.05 #Step size
x = np.arange(xlim[0],xlim[1],d)  #Values along x axis
y = np.arange(ylim[0],ylim[1],d)  #    -||-     y axis
X,Y = np.meshgrid(x,y)            #X = [[xi for xi in x] for yi in y]], Y analogous
Z = X*np.exp(-X**2 - Y**2)        #z val for all x,y combinations: Xc,Yc,Zc dim agree

#Init N-dimensional interpolator
interp = LinearNDInterpolator(list(zip(X.flatten(), Y.flatten())), Z.flatten())

#Approximative grid
dapprox=0.3
xa = np.arange(xlim[0],xlim[1],dapprox)
ya = np.arange(ylim[0],ylim[1],dapprox)
Xa,Ya = np.meshgrid(xa,ya)  # 2D grid for interpolation

#Interpolate on the fine grid to get points corresponding to approx. grid
Za = interp(Xa, Ya)

#Plot fine grid
fig = plt.figure(figsize=(10,5))
ax1 = fig.add_subplot(121, projection='3d')
ax1.plot_surface(X, Y, Z)
plt.title('Fine grid')
plt.xlabel('x')
plt.ylabel('y')

#Plot coarse/approximative grid
ax2 = fig.add_subplot(122, projection='3d')
ax2.plot_surface(Xa, Ya, Za)
plt.title('Approx. grid')
plt.xlabel('x')
plt.ylabel('y')

plt.savefig('NDinterpolate.pdf')

