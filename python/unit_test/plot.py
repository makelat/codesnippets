#An illustration of implementing plot reproducibility tests.
#Here, the function plotter produces a plot that must be reproducible even if the code is
#modified. To this end, a directory for storing test files is made, for storing plot output
#as ASCII data. If no prior output data files exist, no issues are raised, and a reference 
#file is initiated. Files produced later are then compared with the reference, and a warning
#message is printed if new output does not agree with the reference.
#The code works as is, but the TODO lines show potential places for the user to generalize
import matplotlib.pyplot as plt 
import numpy as np
import os

def plotTest(plotdata,testtag,testsubdir=''):
    
    #Ensure relevant test directory structure exists
    testdir = 'tests/'+testsubdir
    if testdir[-1]!='/': testdir+='/'
    testdirsplit = [t for t in testdir.split('/') if len(t)!=0]
    for i in range(1,len(testdirsplit)+1):
        currentpath = '/'.join(testdirsplit[:i])
        if not os.path.exists(currentpath): 
            os.mkdir(currentpath)
            
    #The first output is named "*_REFERENCE"; compare later-produced outputs with that
    suffix = '.txt'
    initmode = True
    ref = '_REFERENCE'
    outputpath = testdir + testtag
    if os.path.exists(outputpath+ref+suffix): 
        initmode = False
        ref=''
    
    #Write x and y axes's data to output file, one column for each
    #TODO plotdata output is assumed to be from a simple plt.plot here.
    #     Will be different for e.g. histograms or multidimensional plots
    f = open(outputpath+ref+suffix,"w")
    plotdataT = np.array(plotdata[-1].get_data()).T
    for vec in plotdataT:
        for x in vec:
            f.write(str(x)+"    ")
        f.write('\n')
    f.close()

    #If a reference file already exists, compare this output to that    
    if not initmode:
        print('TODO')
        xref = np.loadtxt(outputpath + '_REFERENCE' + suffix, usecols=0)
        yref = np.loadtxt(outputpath + '_REFERENCE' + suffix, usecols=1)
        x    = np.loadtxt(outputpath                + suffix, usecols=0)
        y    = np.loadtxt(outputpath                + suffix, usecols=1)
        #TODO here we check exact agreement, works for ints.
        #     Floats would require a simple tolerance criterion
        xagree = sum([x[i] == xref[i] for i in range(len(x))])
        yagree = sum([y[i] == yref[i] for i in range(len(y))])
        if xagree != len(x) or yagree != len(y):
            print('WARNING: test '+outputpath+' failed!')
        else: print('Test '+outputpath+' passed')
#END plotTest


#A usual function to produce a plot.
#The only difference to a "vanilla" function is to wrap plt.plot w/in plotTest(...)
def plotter():
    
    #Load sample data to be plotted
    filename="plotdata.dat"    
    x = np.loadtxt(filename,usecols=0)
    y = np.loadtxt(filename,usecols=1)
       
    #Plot -- here, wrap plt.plot into a function utilizing the output for tests
    plotTest(plt.plot(x,y,label=r'$y=x^2$'),\
             testsubdir = 'plot',\
             testtag = 'test_220131_01')  #Assign an individual output tag
    #TODO the testtag above must be different for all produced plots.
    #     An example convention is to give tags consisting of dates and test indices:
    #     [date of incorporating test]_[Is this the 1st/2nd/... test implemented today?]
    
    # Title, axis labels and legend
    # Illustrate adding variable stuff into the label string
    plt.ylabel(r'$y$')
    plt.xlabel(r'$x$') 
    plt.legend(frameon=False)
    savename = "plot"+".pdf"
    plt.savefig(savename)
    plt.clf()

    
#"Main" function calls
plotter()
