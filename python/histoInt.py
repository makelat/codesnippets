# importing the required modules
import matplotlib.pyplot as plt 
import numpy as np

def integrate(bins,heights):
    ret = 0
    for i in range(len(bins)-1):
        ret += heights[i]*(bins[i+1]-bins[i])
    return ret

### MAIN

#blim = np.logspace(1,np.log10(10.),10)
x    = [1.,1.,2.,3.,4.,4.,4.,5.,5.,5.,5.,6.,6.,7.,8.,8.,9.,10.]
wgt  = 0.5*np.ones(len(x))

#"hist" returns the bins' [0] heights [1] limits:
out = plt.hist(x,bins=np.linspace(1.,10.,10),weights=wgt)
print out
print integrate(out[1],out[0])
