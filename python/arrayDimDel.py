import numpy as np

#AUX function to remove i:th column and row from array arr
def dimDel(arr, i):
    ret = np.delete(arr, i, 0)
    ret = np.delete(ret, i, 1)
    return ret

plabels = ['pi','K','c']
gens = ['S','D','E','Q']
Ng = len(gens)
lambdas=[]
for i in range(Ng-1):
    lambdas.append('l'+str(i))

Arow=[x+"_"+y for y in plabels for x in lambdas]
A=[Arow for i in range(len(Arow))]

print('Original A=\n',A)

#A pair of indices, the indices corresponding to which must not be deleted
#1st particle index, 2nd lambda (~"gen") index
notDel=[[0,1],\
        [1,1]]

ipart0=min([n[0] for n in notDel])
ipart1=max([n[0] for n in notDel])
igen0 =min([n[1] for n in notDel])
igen1 =max([n[1] for n in notDel])

#Profile all other parameters one at a time
for i in range(((ipart1+1)*(Ng-1)),len(A)):             #Profile over particle types after the interesting ones
    A = dimDel(A, (ipart1+1)*(Ng-1))
for i in range(((ipart0+1)*(Ng-1)),((ipart1)*(Ng-1))):  #    -||-     particle types between       -||-
    A = dimDel(A, (ipart0+1)*(Ng-1))
for i in range((ipart0*(Ng-1))):                        #    -||-     particle types before        -||-
    A = dimDel(A, 0)
#At this point, matrix dimensions are ([#distinct ptypes]*[#lambdas]) x ([#distinct ptypes]*[#lambdas])
for iptype in np.flip(range(int(len(A)/(Ng-1)))):
    for ilambda in np.flip(range(Ng-1)):
        if ilambda not in [igen0,igen1]:
            A = dimDel(A, iptype*(Ng-1)+ilambda)

print('Reduced A=\n',A)
