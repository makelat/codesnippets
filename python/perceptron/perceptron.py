#This contains the perceptron definition & main calls to tests, plots etc.

#For further explanation, see pseudodata.py, which you can use to generate the 
#files X_train, y_train, X_test, y_test, in case they don't already exist.

#For simplicity, we assume that the training data can always be separated 
#linearly; if not, this would lead to conergence problems.

import matplotlib.pyplot as plt 
import numpy as np

### PERCEPTRON

#Train a perceptron classifier
#Param:  X    Input data, N x 2: points in a 2D plane
#        y    Input data, N x 1: labels +- dividing points in X into two classes
def perceptron(X,y):
    
    k = 0           #To collect number of retries in loop
    kMax = 1000     #Loop safety check
    
    #Check input dimensions
    if len(X)==0 or len(y)!=len(X):
        print('WARNING: cannot run perceptron, dimension mismatch')
        return [0,0],0
    
    d = len(X[0])
    ret = np.zeros(d)
    atStart = True  #Temp, false after 1st iteration
    i = 0           #Current index
    Ncorrect = 0
    while Ncorrect < len(X) and k < kMax:
        xt = np.array(X[i,:]).T
        yt = y[i]
        
        a = np.sign(yt*np.dot(np.array(ret).T,xt))
        
        if atStart or a < 0:
            Ncorrect = 0;
            ret = ret + np.multiply(yt,xt)
            k += 1
            atStart = False;
        else: Ncorrect += 1
        
        i += 1
        if i >= len(X): i = 1
    
    return ret,k


### TESTS AND PLOTS

#Test the perceptron result theta on a 2nd dataset, 
def test(theta, X_test, y_test):
    err = 0  #Init
    m = len(X_test)
    if m>0:
        y_pred = np.sign(np.dot(X_test,theta))
        #Check predicted against the true class labels
        err = sum(abs(np.sign(y_test - y_pred)))/m
    print('Perceptron error:',err)
    return err

#Plot data and decision boundary.
#Param:  X        Data read from tables,   N x 2
#        y        Data read from tables,   N x 1
#        theta    Perceptron return value, 2 x 1
def plotter(X,y,theta,plotname):
    
    plt.clf()
    #Plot points w/ y>0 label in teal
    x1=[X[i,0] for i in range(len(X)) if y[i]==1]
    y1=[X[i,1] for i in range(len(X)) if y[i]==1]
    plt.plot(x1, y1,color='teal',marker='.',lw=0.)
    
    #Plot points w/ y<0 label in brown
    x2=[X[i,0] for i in range(len(X)) if y[i]==-1]
    y2=[X[i,1] for i in range(len(X)) if y[i]==-1]
    plt.plot(x2, y2,color='brown',marker='.',lw=0.)

    #Decision boundary
    if len(theta)==2:
        xmax = max(max(x1),max(x2))
        ymax2 = 1
        if theta[1]>0: ymax2 = -xmax*theta[0]/theta[1]
        plt.plot([0, xmax], [0, ymax2], color='black')
    
    #plt.xlabel(r'$x$') 
    #plt.ylabel(r'$y$') 
    plt.savefig(plotname+'.pdf')

#Train using dataset a, plot
X = np.loadtxt('X_train.dat')
y = np.loadtxt('y_train.dat')
print('Loaded X and y (train)')
theta,k = perceptron(X,y)  #theta: resulting parameters, k~iterations
plotter(X,y,theta,'train')
#print('k',k)

#Test the trained classifier, plot it
X_test = np.loadtxt('X_test.dat')
y_test = np.loadtxt('y_test.dat')
print('Loaded X and y (test)')
test(theta,X_test,y_test)
plotter(X_test,y_test,theta,'test')
