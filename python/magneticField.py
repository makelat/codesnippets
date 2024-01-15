#Compute and draw the path of a charged particle moving in a magnetic field

# importing the required modules
import matplotlib.pyplot as plt 
import numpy as np
import math

c      = 2.99792458e8           #Speed of light in vacuum [m/s]
mNU2SI = 1.782661921e-36        #Mass in natural units (NU) [eV] to SI [kg]
eV2J   = 1.602176634e-19        #Electronvolt to Joule ratio
pNU2SI = 5.344329812061466e-28  #Turn momentum in eV to SI units

q=-1.602176634e-19 #Electron charge [C=As]
#m=0.51099895e6  #Electron mass
m=105.6583745e6 #Muon mass  [eV/c^2]
#m=1776.86e6     #Tau mass
m=m*mNU2SI

#TODO WIP, wrong sign? Check factors... template for a 
#simple analytic formula cross-check for the num diff eq sol.
def BpathSimple(P_in,s_in,dt,Nt):
    P=np.multiply(pNU2SI,P_in)   #Convert to SI
    xP=[]
    zP=[]
    #Find particle's path in magnetic field
    Plen = math.sqrt(sum(elem**2. for elem in P))
    qpB = q*np.cross(P,B)
    qpBlen = math.sqrt(sum(elem**2. for elem in qpB)) 
    R = Plen**2/qpBlen
    print 'R='+str(R)
    for it in range(Nt):
        x = s_in[0] + R*np.cos(it*dt) - R
        y = s_in[2] + R*np.sin(it*dt)
        #print x,y
        xP.append(x)
        zP.append(y)    
    return xP,zP

#Find a (charged) particle's path in a magnetic field
#By solving new location numerically from
#  m\vec{a} = q \vec{v} \times \vec{B}
def Bpath(P_in,s_in,dt,Nt):
    P=np.multiply(pNU2SI,P_in)   #Convert to SI
    v=np.multiply(1./m,P)        #Velocity
    vlen0 = math.sqrt(sum(elem**2. for elem in v))
    s=s_in
    xP=[]
    zP=[]
    #Find particle's path in magnetic field
    for it in range(Nt):
        xP.append(s[0])
        zP.append(s[2])    
        qvB = q*np.cross(v,B)
        v = np.add(v,(dt/m)*qvB)
        vlen1 = math.sqrt(sum(elem**2. for elem in v))
        v=np.multiply(vlen0/vlen1,v)
        s = np.add(s,np.multiply(dt,v))
    return xP,zP

### MAIN

paths=[]
B=[0,1,0]  #Magnetic field [T], 1 T = 1 kg/s^2/A
s=[0,0,0]  #Init. spatial crd.s [m]
P=[0,0,360]  #Momentum
#P=[4.334,14.078,361.937]


#Arg.s: momentum, position, t-step length, #t-steps
#paths.append(Bpath(P,s,1e-10,1000000))
#paths.append(Bpath(P,s,1e-9, 100000 ))
#paths.append(Bpath(P,s,1e-8, 10000  )) #Definitely OK i.e. converged
#paths.append(Bpath(P,s,1e-6, 100  )) #Slight deviation, ~OK
#paths.append(Bpath(P,s,1e-5, 10  ))  #Way too much deviation

#paths.append(BpathSimple(P,s,1e-3, 700))
paths.append(Bpath(P,s,1e-11, 1000))

#Plot paths
for iPath in range(len(paths)):
    plt.plot(paths[iPath][0], paths[iPath][1]) 
plt.xlabel(r'$x$ [m]') 
plt.ylabel(r'$z$ [m]') 
plt.savefig("magneticField.pdf")
plt.clf()
