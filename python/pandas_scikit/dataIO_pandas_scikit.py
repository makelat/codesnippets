#Importing the required modules. If not installed, do:
#  pip install pandas
#  pip install sklearn
import pandas
from pandas import read_csv
import numpy as np
from matplotlib import pyplot

#CSV=comma-separated-values. The method in this program does not support
#arbitrarily long whitespace delimiters, use a comma

#Open file for reading
filename = r"pima-indians-diabetes.csv" # r in front of string for "raw string"
colnames=['preg','plas','pres','skin','test','mass','pedi','age','class']
data = read_csv(filename, names=colnames)
array = data.values  #preprocessing with scikitlearn needs this

#Correlation matrix
#correlations = data.corr(method='pearson')
#print(correlations)

#Plot correlation matrix
#correlations = data.corr()
#fig = pyplot.figure()
#ax = fig.add_subplot(111)
#cax = ax.matshow(correlations, vmin=-1, vmax=1)
#fig.colorbar(cax)
#ticks = np.arange(0,9,1)
#ax.set_xticks(ticks)
#ax.set_yticks(ticks)
#ax.set_xticklabels(colnames)
#ax.set_yticklabels(colnames)
#pyplot.show()

### Preprocessing opt.1: rescale data s.t. min=0, max=1
#from sklearn import preprocessing
#data_scaler = preprocessing.MinMaxScaler(feature_range=(0,1))
#data_rescaled = data_scaler.fit_transform(array)

### Preprocessing opt.2: normalize column length to 1
#from sklearn.preprocessing import Normalizer
#Data_normalizer = Normalizer(norm='l1').fit(array)
#Data_normalized = Data_normalizer.transform(array)

### Preprocessing opt.3: binarize
#from sklearn.preprocessing import Binarizer
#Data_binarizer = Binarizer(norm='l1').fit(array)
#Data_normalized = Data_binarizer.transform(array)

### Preprocessing opt.3: standardize (mean 0, std.dev 1, good for Gaussian data)
#from sklearn.preprocessing import StandardScaler
#from numpy import set_printoptions
#data_scaler = StandardScaler().fit(array)
#data_rescaled = data_scaler.transform(array)
