import numpy as np
from copy import deepcopy
from multiprocessing import Pool, cpu_count

def func(vin):
    print(vin)
    ret = 0
    for iv,v in enumerate(vin):
        ret += v**(iv+1)
    return ret

#Generalize arbitrary #nested loops below via recursion. However,
#don't evaluate the function, simply shape a matrix of input args
def recurse(x,ls,pars,atEnd):
    ret=[]
    if atEnd:
        return pars
    else:
        for lsi in ls:
            parssub = deepcopy(pars)
            parssub.append(lsi)
            ret.append(recurse(x[0],ls,parssub,x.ndim==1))
    return ret

def funchandle(handleinputspercpu):
    ret=[]
    for handleinput in handleinputspercpu:
        #N.B. if func needs multiple args, they must be expressed as numbers and 
        #parsed here from handleinput which must be a flat list/array of numbers, s.t.
        #e.g. func(vector,int) is achieved via func(handleinput[:-1],handleinput[-1])
        ret.append(func(handleinput))
    return np.array(ret)

#Here, recursion is only used for forming a table of input args and
#values are evaluated via this parent function, improving threadability
def HessianMapFormer():
    dx=0.01
    ndx=5   #Evaluations performed at 5 points along a direction to get Hessian stencil
    ndim=3  #N.o. variables / "spatial dimensions x,y,..."
    ls = np.linspace(-2*dx,2*dx,ndx)
    dimlist = np.ones(ndim,int)
    dimlist = np.multiply(ndx,dimlist)
    x = np.empty(dimlist,dtype=float)
    x = np.array(recurse(x,ls,[],False))
    xshape=x.shape  #Check rank and subdimensions of x
    #Reshape x into rank 2, w/ each index retrieving a set of params for func
    xflat=x.flatten()
    xcalcshape=xflat.reshape(int(len(xflat)/ndim),ndim)
    xcalcd=np.empty(len(xcalcshape),dtype=float)
    ncpu = 1 #cpu_count()
    calcspercpu = int(len(xcalcshape)/ncpu)

    #Init inputs for multiprocessing to compute (most) entries of the Hessian
    xcalcshapecpu = np.array([xcalcshape[n*calcspercpu:(n+1)*calcspercpu] for n in range(ncpu)])

    #The multiprocessing computation itself
    procs = Pool(processes=ncpu)
    xcalcd = np.array(procs.map(funchandle, xcalcshapecpu)).flatten()
    print(xcalcd)

    #If process count was not divisible by ncpu, compute the remaining entries naively
    if ncpu*calcspercpu < len(xcalcshape):
        for extra in xcalcshape[ncpu*calcspercpu:]: 
            pars = deepcopy(extra)
            xcalcd = np.append(xcalcd,func(pars))


    #Reshape results into original x form, but omit the last level of ndim
    xreshaped=np.array(xcalcd).reshape(xshape[:-1])
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
