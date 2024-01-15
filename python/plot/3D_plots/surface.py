# importing the required modules
from mpl_toolkits.mplot3d import axes3d
import matplotlib.pyplot as plt
import numpy as np

x = np.arange(-5,5,0.1)
y = np.arange(-5,5,0.1)
X,Y = np.meshgrid(x,y)
Z = X*np.exp(-X**2 - Y**2)

fig = plt.figure(figsize=(6,6))
ax = fig.add_subplot(111, projection='3d')

#Plot
ax.plot_surface(X, Y, Z)
plt.savefig('surface.pdf')
