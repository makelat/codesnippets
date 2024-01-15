# importing the required modules
import csv
import numpy as np

#CSV=comma-separated-values. The method in this program does not support
#arbitrarily long whitespace delimiters, use a comma
filename = r"data.csv"      #r in front of string for "raw string"

#Open file for reading
with open(filename,'r') as f:
    reader=csv.reader(f, delimiter = ',')
    headers = next(reader)  #getline equivalent? Fetch 1st header line
    data = list(reader)     #Fetch data from the remaining lines
    data = np.array(data).astype(float)
    
print(headers)     #Print column headers from 1st line
print(data.shape)  #Print (Nrows, Ncols)
print(data[:5])    #Print 1st 5 lines' data
