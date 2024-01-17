import numpy as np
from sklearn.svm import SVR
import matplotlib.pyplot as plt

#Generate datapoins
N = 70
ND = 2  #Illustrates generalizing n.o. dimensions, but restrict to 2 for plots
X = np.sort(4.0*np.pi*np.random.rand(N,ND),axis=0)
y = np.array(sum([X[:,i]**(i+1) for i in range(ND)])).flatten()

#Fluctuate data
y += (1.37-np.random.rand(N))

#Define the models. Compare polynomial and radial basis function
pol = SVR(kernel='poly',C=100,gamma="auto",epsilon=0.1,degree=3,coef0=1)
rbf = SVR(kernel='rbf', C=100,gamma=0.1,epsilon=0.1)

#Fit
print('Fitting polynomial')
model_pol = pol.fit(X, y)
print('Fitting radial basis function')
model_rbf = rbf.fit(X, y)

#Produce predictions corresponding to values of X
interp_pol = model_pol.predict(X)
interp_rbf = model_rbf.predict(X)

#Plot data and interpolation results
fig = plt.figure()
ax = plt.axes(projection='3d')
ax.scatter3D(X[:,0], X[:,1], y, facecolor='none', color='green', label='Data')
ax.scatter3D(X[rbf.support_][:,0], X[rbf.support_][:,1], y[rbf.support_],\
             marker='.',color='green',alpha=0.5,label="RBF support vec.")
ax.plot3D(X[:,0],X[:,1],interp_pol,color='gray',label='Polynomial')
ax.plot3D(X[:,0],X[:,1],interp_rbf,color='blue',label='RBF',linestyle='dotted')
plt.xlabel(r'$X_0$')
plt.ylabel(r'$X_1$')
plt.title('Multivariate support vector machine regression')
plt.legend(frameon=False)

plt.savefig('SVR_multivariate.pdf')
