import numpy as np

def func(v):
    abstr=""
    for x in v:
        abstr += str(x)
    return float(abstr)

print("Rank 2")
vec = [1,2,3]
T = np.array([[func([x, y]) for x in vec] for y in vec])
print("Tensor:")
print(T)
print("Gradient:")
print(np.gradient(T))  #Returns [ [matrix of dT/dx vals], [matrix of dT/dy vals] ]
print("Gradient component test [:,:,2,2]")
GTtest = np.empty((T.ndim, T.ndim) + T.shape, dtype=T.dtype)
print(GTtest[:,:,2,2])

print("Rank 3")
T2 = np.array([[[func([x, y, z]) for x in vec] for y in vec] for z in vec])
print("Tensor")
print(T2)
print("Gradient")
GT2=np.gradient(T2)
print(GT2)
print("Gradient component test [:,:,2,2,2]")
GT2test = np.empty((T2.ndim, T2.ndim) + T2.shape, dtype=T2.dtype)
print(GT2test[:,:,2,2,2])
