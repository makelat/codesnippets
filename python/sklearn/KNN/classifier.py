from sklearn.datasets import make_blobs
import matplotlib.pyplot as plt
from sklearn.neighbors import KNeighborsClassifier
from sklearn.neighbors import KDTree, BallTree
import numpy as np

#Generate training set
seed = 42  #Random seed for dataset reproducibility
N = 200     #Points to generate
Nfeat = 2   #The number of "crds" / dimensions in X. 2 for plottability here.
Ncent = 3   #How many groups to label generated data into?
Xtrain,ytrain = make_blobs(n_samples=N,\
                           n_features=Nfeat,\
                           centers=Ncent,\
                           cluster_std=0.5, center_box=(0.0, 10.0),\
                           shuffle=True,\
                           random_state=seed,\
                           return_centers=False)

#Generate datapoints to classify
Xtest = np.random.rand(50,Nfeat)
Xtest = np.multiply(10,Xtest)


#Train models resorting on alternative algorithms for finding neighbors

#A vanilla k-nearest neighbors (KNN) model
#This should take a time proportional to DN, w/ N data points and D dimensions
knn = KNeighborsClassifier(n_neighbors=7,algorithm='brute')
knn.fit(Xtrain,ytrain)

#There are also tree and ball algorithms for finding the nearest neighbors.
#The tree algorithm uses info like if A,B distant && B,C close => A,C distant
#At best takes a DlogN time, but gets worse at higher dimensions, e.g. DN
kdt = KNeighborsClassifier(n_neighbors=7,algorithm='kd_tree')
kdt.fit(Xtrain,ytrain)

#The ball algorithm looks at a D-sphere when finding the neighbors. Addresses
#issues of KDTree at high dimensions, so DlogN expected at high D
kbt = KNeighborsClassifier(n_neighbors=7,algorithm='ball_tree')
kbt.fit(Xtrain,ytrain)


#Predict labels for a testing sample
ypredKNN = knn.predict(Xtest)
ypredKDT = kdt.predict(Xtest)
ypredKBT = kbt.predict(Xtest)

#Plot
colors=['salmon','dodgerblue','gray']
for i in range(Ncent):
    plt.plot([x for ix,x in enumerate(Xtrain[:,0]) if ytrain[ix]==i],\
             [x for ix,x in enumerate(Xtrain[:,1]) if ytrain[ix]==i],\
             lw=0,marker='o',color=colors[i],\
             label='Train')
    plt.plot([x for ix,x in enumerate(Xtest[:,0]) if ypredKNN[ix]==i],\
             [x for ix,x in enumerate(Xtest[:,1]) if ypredKNN[ix]==i],\
             lw=0,markerfacecolor='white',marker='o',color=colors[i],\
             label='Vanilla')
    plt.plot([x for ix,x in enumerate(Xtest[:,0]) if ypredKDT[ix]==i],\
             [x for ix,x in enumerate(Xtest[:,1]) if ypredKDT[ix]==i],\
             lw=0,marker='x',color=colors[i],\
             label='KDTree')
    plt.plot([x for ix,x in enumerate(Xtest[:,0]) if ypredKBT[ix]==i],\
             [x for ix,x in enumerate(Xtest[:,1]) if ypredKBT[ix]==i],\
             lw=0,marker='.',alpha=0.5,color=colors[i],\
             label='Ball')
plt.legend()
plt.xlabel(r'$x_0$')
plt.ylabel(r'$x_1$')
plt.savefig('classifier.pdf')
