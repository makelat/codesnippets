#This code illustrates some ways to optimize the hessian computation:
#0) Use multiprocessing pool
#1) Form array of function input parameter values (corresponding to +-dx variations) recursively,
#   making it possible to use the same code for arbitrary numbers of variables / dimensions
#2) Give the input +-dx variations as an integer mask, parsed into a vector only later. Makes the
#   arrays stored in memory one dimension smaller
import numpy as np
from copy import deepcopy
from multiprocessing import Pool, cpu_count

dx = 0.01
ndx=5   #Evaluations performed at 5 points along a direction to get Hessian stencil
    
def func(vin):
    ret = 0
    for iv,v in enumerate(vin):
        ret += v**(iv+1)
    return ret

#Generalize arbitrary #nested loops below via recursion. However,
#don't evaluate the function, simply shape a matrix of input args
def recurse(x,ls,pars,atEnd):
    ret=[]
    if atEnd:
        pars2int=0
        nmax = len(pars)
        for n in range(nmax):
            pars2int += pars[n]*10**(nmax-n-1)
        return pars2int
    else:
        for lsi in ls:
            parssub = deepcopy(pars)
            parssub.append(lsi)
            ret.append(recurse(x[0],ls,parssub,x.ndim==1))
    return ret

#Translate an input integer into a vector with doubles 
def paramParser(inputint):
    shift = -0.5*(ndx+1)
    return [dx*(int(nstr)+shift) for nstr in str(inputint)]

def funchandle(handleinputspercpu):
    ret=[]
    for handleinput in handleinputspercpu:
        #N.B. if func needs multiple args, they must be expressed as numbers and 
        #parsed here from handleinput which must be a flat list/array of numbers, s.t.
        #e.g. func(vector,int) is achieved via func(handleinput[:-1],handleinput[-1])
        ret.append(func(paramParser(handleinput)))
    return np.array(ret)

#Here, recursion is only used for forming a table of input args and
#values are evaluated via this parent function, improving threadability
def HessianMapFormer():
    ndim=3  #N.o. variables / "spatial dimensions x,y,..."
    dimlist = np.multiply(ndx,np.ones(ndim,int))
    x = np.empty(dimlist,dtype=int)
    x = np.array(recurse(x,range(1,ndx+1),[],False))
    xshape=x.shape  #Check rank and subdimensions of x
    x = x.flatten()
    print('All '+str(len(x))+' indices to be computed:')
    print(x)
    ncpu = cpu_count()
    calcspercpu = int(len(x)/ncpu)
    nextra = len(x)-ncpu*calcspercpu  #Remainder if n of calcs not divisible by ncpu
    print('#cpu = ',ncpu,', #calculations/cpu = ',calcspercpu)
    print('Computing ',len(x)-nextra,'/',len(x),' entries using multiprocessing:')

    #Init inputs for multiprocessing to compute (most) entries of the Hessian
    xcpu = np.array([x[n*calcspercpu:(n+1)*calcspercpu] for n in range(ncpu)])    
    print(xcpu)
    
    #The multiprocessing computation itself
    procs = Pool(processes=ncpu)
    xcalcd = np.array(procs.map(funchandle, xcpu)).flatten()
    
    #If process count was not divisible by ncpu, compute the remaining entries
    if nextra > 0:
        print('Computing remaining '+str(nextra)+' entries:')
        procs2 = Pool(processes=nextra)
        xcpu2 = np.array([[x[n]] for n in range(len(x)-nextra,len(x))])
        print(xcpu2)
        xcalcdadd = np.array(procs2.map(funchandle,xcpu2)).flatten()
        xcalcd = np.append(xcalcd,xcalcdadd) #func(paramParser(pars)))

    #Reshape results into original x form, but omit the last level of ndim
    xreshaped=np.array(xcalcd).reshape(xshape)
    #Construct hessian
    x_grad = np.gradient(xreshaped) 
    hessian = np.array(list(map(np.gradient, x_grad)))
    for i in range(ndim):
        hessian = hessian[:,:,2]
    return hessian/dx**2

# MAIN
HMapF=HessianMapFormer()
print("HessianMapFormer")
print(HMapF)
