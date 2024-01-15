#Modify an arbitrarily deep array via recursion instead of nested #loops=?
import numpy as np

#An AUX function applied to the array's bottom level entries
def func(x):
    return 10*x

#The bool atEnd turns True upon entering the array x's final depth level
#Returns the resulting array as a list
def recurse(x,atEnd):
    ret=[]
    if atEnd:
        return func(x)
    else:
        for ix,xsub in enumerate(x):
            ret.append(recurse(xsub,x.ndim==1))
    return ret
    
# MAIN
dim = 3
arr = np.random.rand(dim,dim,dim)

print("Input array")
print(arr)

arr = np.array(recurse(arr,False))
print("Array modified recursively")
print(arr)
