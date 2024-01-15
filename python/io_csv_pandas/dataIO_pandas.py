# importing the required modules
import pandas
from pandas import read_csv
import numpy as np
from matplotlib import pyplot

#CSV=comma-separated-values. The method in this program does not support
#arbitrarily long whitespace delimiters, use a comma

#Open file for reading
filename = r"data_noHeader.csv" # r in front of string for "raw string"
colnames=['x','y']
data = read_csv(filename, names=colnames)

print(data.shape)  #Print (Nrows, Ncols)
print(data[:5])    #Print 1st 5 lines' data

print(data.dtypes)   #Print datatypes, e.g. float64 (pandas-specific call)

#Use pandas to produce histograms and pyplot to immediately show them
data.hist()
pyplot.show()

#Density plot
data.plot(kind='density', subplots=True, sharex=False)
pyplot.show()

#Box & whisker -- show median, 25% and 75%
data.plot(kind='box', subplots=True, sharex=False, sharey=False)
pyplot.show()

#Correlation matrix
correlations = data.corr(method='pearson')
print(correlations)

#Plot correlation matrix
correlations = data.corr()
fig = pyplot.figure()
ax = fig.add_subplot(111)
cax = ax.matshow(correlations, vmin=-1, vmax=1)
fig.colorbar(cax)
ticks = np.arange(0,9,1)
ax.set_xticks(ticks)
ax.set_yticks(ticks)
ax.set_xticklabels(colnames)
ax.set_yticklabels(colnames)
pyplot.show()

#Scatter plot
scatter_matrix(data)
pyplot.show()
