#There are many ways to compute the Hessian numerically, using more or less Python features.
#However, the different versions are not necessarily optimal in terms of memory handling etc.
#Here is a selection of some ways relying more on Python features.
#The reader is however advised to have a look at hessian_elements.py as well for the best reference.

import numpy as np
from copy import deepcopy
from multiprocessing import Pool, cpu_count

def func(vin):
    ret = 0
    for iv,v in enumerate(vin):
        ret += v**(iv+1)
    return ret

#Generalize arbitrary #nested loops below via recursion.
def recurse(x,ls,pars,atEnd):
    ret=[]
    if atEnd:
        return func(pars)
    else:
        for lsi in ls:
            parssub = deepcopy(pars)
            parssub.append(lsi)
            ret.append(recurse(x[0],ls,parssub,x.ndim==1))
    return ret

#Do not evaluate the function, simply shape a matrix of input args
def recurseFormer(x,ls,pars,atEnd):
    ret=[]
    if atEnd:
        return pars
    else:
        for lsi in ls:
            parssub = deepcopy(pars)
            parssub.append(lsi)
            ret.append(recurseFormer(x[0],ls,parssub,x.ndim==1))
    return ret


def Hessian():
    dx=0.01
    ndx=5   #Evaluations performed at 5 points along a direction to get Hessian stencil
    ndim=3  #N.o. variables / "spatial dimensions x,y,..."
    ls = np.linspace(-2*dx,2*dx,ndx)
    dimlist = np.ones(ndim,int)
    dimlist = np.multiply(ndx,dimlist)
    #This produces the same...
    #    x = np.array([[[func([x1, x2, x3]) for x3 in ls] for x2 in ls] for x1 in ls])
    #...as this
    #    x = np.empty(dimlist,dtype=float)
    #    for ix1,x1 in enumerate(ls):
    #        for ix2,x2 in enumerate(ls):
    #            for ix3,x3 in enumerate(ls):
    #                x[ix1,ix2,ix3] = func([x1, x2, x3])
    #Generalization to unknown #[nested loops]:
    x = np.empty(dimlist,dtype=float)
    x = np.array(recurse(x,ls,[],False))
    # calculate hessian
    x_grad = np.gradient(x) 
    hessian = np.empty((x.ndim, x.ndim) + x.shape, dtype=x.dtype) 
    for k, grad_k in enumerate(x_grad):
        tmp_grad = np.gradient(grad_k) 
#        print("grad_k at ",k)
#        print(grad_k)
        for l, grad_kl in enumerate(tmp_grad):
            hessian[k, l] = grad_kl
    # return
    ret = hessian
    print('test')
    print(hessian)
    for i in range(ndim):
        ret = ret[:,:,2]
    return ret/dx**2

#ALT implementation based on the Hessian's symmetry:
#only compute upper triangle matrix and copy values to lower
def HessianALT():
    dx=0.01
    ndx=5   #Evaluations performed at 5 points along a direction to get Hessian stencil
    ndim=3  #N.o. variables / "spatial dimensions x,y,..."
    ls = np.linspace(-2*dx,2*dx,ndx)
    dimlist = np.ones(ndim,int)
    dimlist = np.multiply(ndx,dimlist)
    x = np.empty(dimlist,dtype=float)
    x = np.array(recurse(x,ls,[],False))
    # calculate hessian
    x_grad = np.gradient(x) 
    hessian = np.empty((x.ndim, x.ndim) + x.shape, dtype=x.dtype) 
    for k, grad_k in enumerate(x_grad):
        tmp_grad = np.gradient(grad_k)[k:] #FIXME to be truly useful, should have sth like grad_k[k:]..[k:] (ndim times [k]:)
        for l, grad_kl in enumerate(tmp_grad):
            hessian[k, l+k] = grad_kl
    # insert missing values and return
    ret = hessian
    for i in range(ndim):
        ret = ret[:,:,2]
    for n in range(ndim-1):
        for m in range(n+1,ndim):
            ret[m, n] = ret[n, m]
            print(m,n,ret[m,n])
    return ret/dx**2

#This is a 1-CPU version of HessianMP, shows how the idea of pool generalizes map
def HessianMap():
    dx=0.01
    ndx=5   #Evaluations performed at 5 points along a direction to get Hessian stencil
    ndim=3  #N.o. variables / "spatial dimensions x,y,..."
    ls = np.linspace(-2*dx,2*dx,ndx)
    dimlist = np.ones(ndim,int)
    dimlist = np.multiply(ndx,dimlist)
    x = np.empty(dimlist,dtype=float)
    x = np.array(recurse(x,ls,[],False))
    # calculate hessian
    x_grad = np.gradient(x) 
    hessian = np.array(list(map(np.gradient, x_grad)))
    for i in range(ndim):
        hessian = hessian[:,:,2]
    return hessian/dx**2

def HessianMP():
    dx=0.01
    ndx=5   #Evaluations performed at 5 points along a direction to get Hessian stencil
    ndim=3  #N.o. variables / "spatial dimensions x,y,..."
    ls = np.linspace(-2*dx,2*dx,ndx)
    dimlist = np.ones(ndim,int)
    dimlist = np.multiply(ndx,dimlist)
    x = np.empty(dimlist,dtype=float)
    x = np.array(recurse(x,ls,[],False))
    # calculate hessian
    x_grad = np.gradient(x) 
    procs = Pool(processes=len(x_grad))
    hessian = np.array(procs.map(np.gradient, x_grad))
    for i in range(ndim):
        hessian = hessian[:,:,2]
    return hessian/dx**2

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
    x = np.array(recurseFormer(x,ls,[],False))
    xshape=x.shape  #Check rank and subdimensions of x
    #Reshape x into rank 2, w/ each index retrieving a set of params for func
    xflat=x.flatten()
    xcalcshape=xflat.reshape(int(len(xflat)/ndim),ndim)
    xcalcd=np.empty(len(xcalcshape),dtype=float)
    ncpu = cpu_count()
    calcspercpu = int(len(xcalcshape)/ncpu)

    #Init inputs for multiprocessing to compute (most) entries of the Hessian
    xcalcshapecpu = np.array([xcalcshape[n*calcspercpu:(n+1)*calcspercpu] for n in range(ncpu)])

    #The multiprocessing computation itself
    procs = Pool(processes=ncpu)
    xcalcd = np.array(procs.map(funchandle, xcalcshapecpu)).flatten()

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
H=Hessian()
print("Hessian")
print(H)

H2=HessianALT()
print("HessianALT")
print(H2)

HMap=HessianMap()
print("HessianMap")
print(HMap)

HMP=HessianMP()
print("HessianMP")
print(HMP)

HMapF=HessianMapFormer()
print("HessianMapFormer")
print(HMapF)
