#An old-fashioned implementation of the Hessian, requiring minimal RAM but
#upgraded by multiprocessing and computing only upper triangle (use symmetry)
import numpy as np
from copy import deepcopy
from multiprocessing import Pool, cpu_count
from functools import partial

def func(vin):
    ret = 0
    for iv,v in enumerate(vin):
        ret += v**(iv+1)
    return ret

def HessianElement(point,ix,jx):
    dx=0.01
    ipjp = deepcopy(point)
    ipjp[ix] += dx
    ipjp[jx] += dx
    ipjm = deepcopy(point)
    ipjm[ix] += dx
    ipjm[jx] -= dx
    imjp = deepcopy(point)
    imjp[ix] -= dx
    imjp[jx] += dx
    imjm = deepcopy(point)
    imjm[ix] -= dx
    imjm[jx] -= dx
    return (func(ipjp) - func(ipjm) - func(imjp) + func(imjm))/(4.0*dx**2)
    
def funchandle(handleinputspercpu,point):
    ret=[]
    for indexpair in handleinputspercpu:
        #N.B. if func needs multiple args, they must be expressed as numbers and 
        #parsed here from handleinput which must be a flat list/array of numbers, s.t.
        #e.g. func(vector,int) is achieved via func(handleinput[:-1],handleinput[-1])
        ret.append(HessianElement(point,indexpair[0],indexpair[1]))
    return np.array(ret)

#Here, recursion is only used for forming a table of input args and
#values are evaluated via this parent function, improving threadability
def Hessian(point):

    ndim=len(point)  #N.o. variables / "spatial dimensions x,y,..."

    #Gather indices for which to compute values
    indexpairs = []
    for ix in range(ndim):
        for jx in range(ix,ndim):
            indexpairs.append([ix,jx]) 

    #Compute most entries in upper triangle using multiprocessing
    ncpu = 1 # cpu_count()
    ncpu = min(ncpu,len(indexpairs))
    print('ncpu = '+str(ncpu))
    procs = Pool(processes=ncpu)
    calcspercpu = int(len(indexpairs)/ncpu)
    indicespercpu = np.array([indexpairs[n*calcspercpu:(n+1)*calcspercpu] for n in range(ncpu)])
    UT = np.array(procs.map(partial(funchandle,point=point), indicespercpu))
    
    #If process count was not divisible by ncpu, compute the remaining entries naively
    nextra = len(indexpairs) - ncpu*calcspercpu  #How many computations remain after first pool
    if nextra > 0:
        procs2 = Pool(processes=nextra)
        indicespercpu2 = np.array([[indexpairs[n]] for n in range(len(indexpairs)-nextra,len(indexpairs))])
        UTadd = np.array(procs.map(partial(funchandle,ndim=ndim,detector=detector,proc=proc,radN=radN,\
                                           fstat=fstat,usefs=usefs,usegp=usegp),\
                                   indicespercpu2)).flatten()
        UT = np.append(UT,UTadd)
    
    #Form upper triangle matrix out of the flat list in UT
    print('UT',list(UT))
    Hessian = np.zeros([ndim,ndim])
    Hessian[np.triu_indices(ndim, 0)] = UT
    
    #Fill lower triangle based on symmetry
    for ix in range(ndim):
        for jx in range(ix+1,ndim):
            Hessian[jx,ix] = Hessian[ix,jx]
    return Hessian

# MAIN
ndim=3
point = np.zeros(ndim)  #Compute hessian at t
print("Hessian")
print(Hessian(point))
