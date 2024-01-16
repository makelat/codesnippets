import numpy as np
from sklearn.svm import SVR
import matplotlib.pyplot as plt

#Generate datapoins
N = 100
X = np.sort(3.0*np.pi*np.random.rand(N,1),axis=0)
y = np.cos(X).flatten()

#Fluctuate data
y += (1.37-np.random.rand(N))

#Define the model
kernelstr='rbf'
#kernelstr='poly'  #For comparison, a 3rd degree polynomial would perform worse
if kernelstr=='poly':
    svr = SVR(kernel=kernelstr,C=100,gamma="auto",epsilon=0.1,degree=3,coef0=1)
else:
    svr = SVR(kernel=kernelstr,C=100,gamma=0.1,epsilon=0.1)

#Fit
model = svr.fit(X, y)

#Produce predictions corresponding to values of X
interp = model.predict(X)

#Apply the model prediction on different x-values, also extrapolation,
#illustrating model behavior outside the training region
X2 = np.sort(5.0*np.pi*np.random.rand(2*N,1),axis=0)
extrap = model.predict(X2)

#Plot
plt.plot(X, interp,color='gray',  label=kernelstr+' interp.')
plt.plot(X2,extrap,color='maroon',label=kernelstr+' extrap.',linestyle='dotted')
plt.scatter(X[svr.support_],\
            y[svr.support_],\
            marker='.',color='black',label="Support vectors")
plt.scatter(X[np.setdiff1d(np.arange(len(X)), svr.support_)],\
            y[np.setdiff1d(np.arange(len(X)), svr.support_)],\
            marker='x',color='dodgerblue',label="Other training data")
plt.xlabel(r'$x$')
plt.ylabel(r'$y$')
plt.title('Support vector machine regression')
plt.legend(frameon=False)

plt.savefig('support_vector_machine_regression.pdf')
