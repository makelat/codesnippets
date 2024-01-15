# A simple example to illustrate the importance of list copying
import numpy as np

vals = np.linspace(-1,1,3)
N=2
ret=[]

def arrPlus(arr,vec):
    ret=[]
    for a in arr:
        for v in vec:
            #HOX! tmp=a would use reference i.e. manipulating tmp will change a!
            tmp=a.copy()  #This way, a is independent of tmp
            print("a=",a)
            print("tmp=",tmp)
            print("Appending",v)
            tmp.append(v)
            print("a=",a," should be unchanged")
            print("tmp=",tmp," should have changed")
            print("\n")
            ret.append(tmp)
    return ret

ret=[[x] for x in vals]
for i in range(N):
    ret = arrPlus(ret,vals)

print(ret)
