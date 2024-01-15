import sklearn
from sklearn.datasets import load_breast_cancer
from sklearn.model_selection import train_test_split
from sklearn.naive_bayes import GaussianNB
from sklearn.metrics import accuracy_score
from sklearn.metrics import confusion_matrix

#Load example dataset provided with scikit-learn
data = load_breast_cancer()

#Check
label_names   = data['target_names']
labels        = data['target']
feature_names = data['feature_names']
features      = data['data']
   
#Will output how the data are labeled: 
#either 'malignant' or 'benign' cases
print(label_names)

#Print the available features, along with the corresponding values
for i in range(len(feature_names)):
    print(feature_names[i])
    print(features[i])

#Split data into training and testing parts
train, test, train_labels, test_labels = train_test_split(
   features,labels,test_size = 0.40, random_state = 42
)

#Init naive Bayes classifier / model, training phase
gnb = GaussianNB()
model = gnb.fit(train, train_labels)

#Predictions for evaluation purposes: malignant vs benign cases
preds = gnb.predict(test)
print(preds)

#Confusion matrix: check 
# [[true positives (TP),  false positives (FP)],
#  [false negatives (FN), true negatives (TN)]]
CM = confusion_matrix(test_labels,preds)
print('Confusion matrix\n',CM)
TP = CM[0,0]
FP = CM[0,1]
FN = CM[1,0]
TN = CM[1,1]

#Various metrics for the classifier's performance:
print('Precision: '   + str(TP/(TP+FP))) #Goodness in IDing pos
print('Specificity: ' + str(TN/(TN+FP))) #Goodness in IDing negs
print('Recall: '      + str(TP/(TP+FN)))

#Accuracy: equivalent to (TP+TN)/(TP+FP+FN+TN),
#but can also be called already after instantiating classifier
print('Accuracy: '+str(accuracy_score(test_labels,preds)))
