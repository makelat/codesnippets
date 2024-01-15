# importing the required modules
import matplotlib.pyplot as plt 
import numpy as np

filename="plotdata.dat"

# Indexing starts from 0
x   = np.loadtxt(filename,usecols=0)
y   = np.loadtxt(filename,usecols=1)
unc = np.loadtxt(filename,usecols=2)
  
perc=1.0  #If uncertainties in %, change to 0.01
  
# Plot
plt.plot(x,y,label=r'$y=x^2$') 
#plt.errorbar(x, y, yerr=K*0.01*unc, fmt='.k');  
plt.fill_between(x, y*(1 - perc*unc), y*(1 + perc*unc),\
                 color='gray', alpha=0.2)
  
# Title, axis labels and legend
# Illustrate adding variable stuff into the label string
yextras=['$ [GeV]$~',' = x^2','$ [a.u.]$~']
plt.ylabel(r'$y'+yextras[1]+'$')  #r'' required for LaTeX
plt.xlabel(r'$x$') 
plt.legend()

savename = "plot"+".pdf"
plt.savefig(savename)
plt.clf()
