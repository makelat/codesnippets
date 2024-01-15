# importing the required modules
import matplotlib.pyplot as plt 
import numpy as np

def vAgreeOLD(a,b):
    tol  = 0.001  #Expect agreement up to e.g. 0.1% for each component
    tolp = 1. + tol
    tolm = 1. - tol
    for ai,bi in zip(a,b):
        if bi>(ai+abs(ai)*tol) or bi<(ai-abs(ai)*tol):
            return False
    return True

def vAgree(a,b):
    tol  = 0.001  #Expect agreement up to e.g. 0.1% for each component
    checks = [bi<(ai+abs(ai)*tol) and bi>(ai-abs(ai)*tol) for ai,bi in zip(a,b)]
    return sum(checks)==len(checks)

v=[1,-2,3]
x=[1,2,3]
w=np.multiply(0.5,v)
u=np.multiply(2.0,w)

print('v',v)
print('w',w)
print('u',u)
print('x',x)
print("Using vAgreeOLD")
print("v==w ",vAgreeOLD(v,w))
print("v==u ",vAgreeOLD(v,u))
print("v==x ",vAgreeOLD(v,x))
print("Using vAgree")
print("v==w ",vAgree(v,w))
print("v==u ",vAgree(v,u))
print("v==x ",vAgree(v,x))
