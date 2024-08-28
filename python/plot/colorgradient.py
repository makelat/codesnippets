# importing the required modules
import matplotlib
import matplotlib.pyplot as plt 
from matplotlib import colors
import matplotlib.cm as cmx
import numpy as np
import os

#Define some polynomials, assign each one a progressively darker/lighter color
nplots=10  #How many polynomials to plot
x=np.linspace(0,2,100)
y=[[xi**n + n for xi in x] for n in range(1,nplots)]
 
#Available sequential color maps; most useful for gradient plots
#colmapname = 'Greys'
#colmapname = 'Purples'
#colmapname = 'Blues'
colmapname = 'Greens'
#colmapname = 'Oranges'
#colmapname = 'Reds'
#colmapname = 'YlOrBr'
#colmapname = 'YlOrRd'
#colmapname = 'OrRd'
#colmapname = 'PuRd'
#colmapname = 'RdPu'
#colmapname = 'BuPu'
#colmapname = 'GnBu'
#colmapname = 'PuBu'
#colmapname = 'YlGnBu'
#colmapname = 'PuBuGn'
#colmapname = 'BuGn'
#colmapname = 'YlGn'
#colmapname = 'binary'
#colmapname = 'gist_yarg'
#colmapname = 'gist_gray'
#colmapname = 'gray'
#colmapname = 'bone'
#colmapname = 'pink'
#colmapname = 'spring'
#colmapname = 'summer'
#colmapname = 'autumn'
#colmapname = 'winter'
#colmapname = 'cool'
#colmapname = 'Wistia'
#colmapname = 'hot'
#colmapname = 'afmhot'
#colmapname = 'gist_heat'
#colmapname = 'copper'
    
#Color map setup
cm = plt.get_cmap(colmapname)
vmax=len(y)-1  #Which number/index returns the lightest color in the palette?
#cNorm = colors.Normalize(vmin=0, vmax=vmax)  #Start from black/white
cNorm = colors.Normalize(vmin=-vmax, vmax=vmax)  #Start spectrum at halfway
scalarMap = cmx.ScalarMappable(norm=cNorm, cmap=cm)

#Plot
for i in range(len(y)):
    plt.plot(x,y[i],color=scalarMap.to_rgba(i),label=str(i))
plt.legend(frameon=False)
plt.yscale('log')
plt.savefig('colorgradient.pdf')
plt.clf()
