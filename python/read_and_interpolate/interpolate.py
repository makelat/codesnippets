# importing the required modules
import matplotlib.pyplot as plt 
import numpy as np

def readfile_txt(filename):
    list_of_lists = []
    with open(filename) as f:
        for line in f:
            if len(line)==0: continue
            if line[0]=="#":continue
            inner_list = [float(elt.strip()) for elt in line.split( )]
            if len(inner_list)==0: continue
            list_of_lists.append(inner_list)
    return np.array(list_of_lists)

def read_and_interpolate(filename,x):
    br=readfile_txt(filename)
    return np.interp(x, br.T[0],br.T[1])

#Interpolate values corresponding to a finer grid than given in data.dat
grid = np.linspace(-2,2,100)
ipvals = [read_and_interpolate("data.dat",g) for g in grid]

#Plot original data vs interpolated values
x = np.loadtxt("data.dat",usecols=0)
y = np.loadtxt("data.dat",usecols=1)
plt.plot(x,y,label=r'Original grid',marker="*") 
plt.plot(grid,ipvals,label=r'Interpolation') 
plt.legend()
plt.savefig("grid_vs_interpolation.pdf")
plt.clf()
