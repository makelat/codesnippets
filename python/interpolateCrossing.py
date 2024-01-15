import numpy as np

#Interpolation function to find crds where the path from v0 to v1 crosses 
#the value tr in the direction of iax=0,1,2=x,y,z
def ipCross(v0,v1,tr,iax):
    #In any dir, crossing crds are the same ratio between v0, v1
    R  = (tr-v0[iax])/(v1[iax]-v0[iax])
    print R
    dv = np.add(v1,np.multiply(-1.,v0))    #dv = v1-v0
    dv = np.multiply(R,dv)
    return np.add(v0,dv)  #v0 + R*dv

v0 = [1.0, -1.0, 458.]
v1 = [1.0,  1.0, 615.]

#z-crd of the threshold plane
tr=v0[2]+0.5*(v1[2]-v0[2])
#tr=520

cross=ipCross(v0,v1,tr,2)
print str(cross[0])+', '+str(cross[1])+', '+str(cross[2])
