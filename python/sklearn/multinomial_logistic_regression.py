import sklearn
from sklearn import datasets
from sklearn import linear_model
from sklearn import metrics
from sklearn.model_selection import train_test_split

#Load sample data
digits = datasets.load_digits()

X = digits.data    #Feature matrix
y = digits.target  #Response vector

#Split X and y into training and test sets
Xtrain, Xtest, ytrain, ytest = train_test_split(X,y,\
                               test_size=0.4,random_state=1)

#Logistic regression object
digreg = linear_model.LogisticRegression()

#Training phase
digreg.fit(Xtrain, ytrain)

#Apply trained model on test set to make predictions
ypred = digreg.predict(Xtest)

#Check how well the trained model did
acc = metrics.accuracy_score(ytest, ypred)*100.0  #%
print("Model accuracy = "+str(acc))
