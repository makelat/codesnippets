import numpy as np
from sklearn import datasets
from sklearn import linear_model
from sklearn.model_selection import train_test_split
import sklearn.metrics as sm
import matplotlib.pyplot as plt

#Generate data
#The format of X and y is such that, with index i running over Ni datapoints, 
#X[i] contains a vector of Nj input values, each producing output(s) y[i][j].
#Here we only implement a function of the form f(x)=y, i.e. considering only j=0
Ni = 50  #Number of datapoints
X = [[x] for x in np.linspace(1,Ni,Ni)]
err = 10 * np.random.random(Ni)  #Add fluctuation
y = [[1.37*X[i][0] + err[i]] for i in range(Ni)]

#Split datapoints 50-50 into training and testing samples
splitdata = train_test_split(X,y,test_size=0.5,random_state=1)
X_train, X_test, y_train, y_test = splitdata

#Model definition and evaluation
reg_linear = linear_model.LinearRegression()
reg_linear.fit(X_train, y_train)

#Predict values for testing x
y_pred = reg_linear.predict(X_test)

#Plot
plt.scatter(X_train, y_train, color='black', label='Training', marker='x')
plt.scatter(X_test,  y_test,  color='maroon',     label='Testing')
plt.plot(   X_test,  y_pred, color='dodgerblue', label='predictions')
plt.title('Linear regression')
plt.xlabel('x')
plt.ylabel('y')
plt.xticks(())
plt.yticks(())
plt.legend(frameon=False)
plt.savefig('linear_regression.pdf')

#Check performance statistics
print("Mean squared error(MSE):  ",sm.mean_squared_error(      y_test, y_pred))
