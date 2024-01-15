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

Talt=[]
for y in vec:
    Tmp=[]
    for x in vec:
        v = [x, y]
        Tmp.append(func(v))
    Talt.append(Tmp)
T2 = np.array(Talt)
print("Alternative algorithm:")
print(T2)

#Demonstrate summing lists within lists
print("sum_i T_{ij} = T_j:")
Tj = [sum(x) for x in zip(*T)]
print(Tj)
print("Alternative algorithm")
Tj2 = [sum(Ti[:]) for Ti in T]
print(Tj)
