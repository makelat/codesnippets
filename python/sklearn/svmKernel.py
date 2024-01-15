#WIP adapted from tutorialspoint

import pandas as pd
import numpy as np
from sklearn import svm, datasets
import matplotlib.pyplot as plt

#Load sample data
iris = datasets.load_iris()
X = iris.data[:, :2]  #Feature matrix
y = iris.target       #Target

#Plot SVM bd.s w/ orig. data
x_min, x_max = X[:,0].min()-1, X[:,0].max()+1
y_min, y_max = X[:,1].min()-1, X[:,1].max()+1
h = (x_max / x_min)/100
xx, yy = np.meshgrid(np.arange(x_min, x_max, h),
                     np.arange(y_min, y_max, h))
X_plot = np.c_[xx.ravel(), yy.ravel()]


C = 1.0  #Regularization param

#SVM classifier object
Svc_classifier = svm.SVC(kernel='linear', C=C).fit(X, y)
Z = svc_classifier.predict(X_plot)
Z = Z.reshape(xx.shape)
plt.figure(figsize=(15, 5))
plt.subplot(121)
plt.contourf(xx, yy, Z, cmap=plt.cm.tab10, alpha=0.3)
plt.scatter(X[:, 0], X[:, 1], c=y, cmap=plt.cm.Set1)
plt.xlabel('Sepal length')
plt.ylabel('Sepal width')
plt.xlim(xx.min(), xx.max())
plt.title('Support Vector Classifier with linear kernel')
Text(0.5, 1.0, 'Support Vector Classifier with linear kernel')  #FIXME rm?

#Try a different kernel (rbf)
#The param 0<gamma<1 can be set to an explicit value or 'auto'
Svc_classifier = svm.SVC(kernel='rbf', gamma ='auto',C=C).fit(X, y)
Z = svc_classifier.predict(X_plot)
Z = Z.reshape(xx.shape)
plt.figure(figsize=(15, 5))
plt.subplot(121)
plt.contourf(xx, yy, Z, cmap=plt.cm.tab10, alpha=0.3)
plt.scatter(X[:, 0], X[:, 1], c=y, cmap=plt.cm.Set1)
plt.xlabel('Sepal length')
plt.ylabel('Sepal width')
plt.xlim(xx.min(), xx.max())
plt.title('Support Vector Classifier with rbf kernel')
Text(0.5, 1.0, 'Support Vector Classifier with rbf kernel')  #FIXME rm?
