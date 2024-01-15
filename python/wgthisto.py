# importing the required modules
import matplotlib.pyplot as plt 
import numpy as np

yRegs=["y0","y1","y2","y3"]
for yReg in yRegs:
    filename="kFactor_NLO+NLL_ak4_muf1mur1_"+yReg+".dat"

    xbins = np.linspace(0,1,11)

    ### Ex.1
    #x   = np.linspace(0,1,10)
    #wgt = 0.5*np.ones(len(x))
    
    ### Ex.2 -- wgt[i] has the wgt corresponding to x[i]
    x  =[0.05, 0.15, 0.25, 0.35, 0.45, 0.55, 0.65, 0.75, 0.85]
    wgt=[32,   16,  8,     4,    2,    1,    0.5,  0.25, 0.125]

    
    # plotting the points  
    plt.hist(x, bins=xbins,fc=(1,0,0,0.5),weights=wgt,lw=0)

    # Title, axis labels and legend
    plt.ylabel('N') 
    plt.xlabel('$x$') 

    # function to show the plot 
    #plt.show() 

    plt.savefig("wgthisto.pdf")
    plt.clf()
