#Illustrate dividing a large array of index pairs into N blocks
#This is useful e.g. for multiprocessing, where each process 
#should be given its share of indices to work with
import numpy as np

#Construct the array of index pairs to divide
dim1, dim2 = 4, 6
a = range(dim1)
a = [[ai,bi] for bi in range(dim2) for ai in a]
print('a =',a)

Nmax = 8  #Divide into max this many blocks, "number of CPUs"
print('Nmax =',Nmax)

print('len(a)/N =',len(a)/Nmax)

step=int(np.ceil(len(a)/Nmax))

test=[a[n*step:(n+1)*step] for n in range(Nmax)]

#This leaves empty vectors into the array if Nmax suboptimal
#print('Result:')
#for t in test: print(t)

N = min(sum([len(t)!=0 for t in test]),Nmax)
print('Should eventually take '+str(N)+' blocks, final array is:')
for t in test[:N]: print(t)
