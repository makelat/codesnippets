# importing the required modules
from mpl_toolkits import mplot3d
import numpy as np
import matplotlib.pyplot as plt

fig = plt.figure()
ax = plt.axes(projection='3d')

# A helix curve
zh = np.linspace(0, 10, 100)
xh = np.sin(zh)
yh = np.cos(zh)

# Points scattered around helix
zs = 10 * np.random.random(100)
xs = np.sin(zs) + 0.1 * np.random.randn(100)
ys = np.cos(zs) + 0.1 * np.random.randn(100)

#Plot
ax.plot3D(   xh, yh, zh, 'gray')
ax.scatter3D(xs, ys, zs, c=zs, cmap='Greens');

plt.savefig('helix_scatter.pdf')
