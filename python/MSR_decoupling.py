#A quick code computing various coefficients needed for using the MSR renormalization scheme

scheme='MSRn'
#scheme='MSRp'

nf=5.0

test=1/3

Rzeta3=1.202056903159594

beta0=0.25*(11.0-2.0*nf/3.0)
beta1=0.0625*(102.0-38.0*nf/3.0)
beta2=0.015625*(  nf*nf*325.0/54.0
                - nf*5033.0/18.0
                + 2857.0/2.0)
beta3=0.00390625*(  nf*nf*nf*1093.0/729.0
                  + nf*nf*50065.0/162.0
                  + nf*nf*Rzeta3*6472.0/81.0
                  - nf*1078361.0/162.0
                  - nf*Rzeta3*6508.0/27.0
                  + 149753.0/6.0
                  + 3564.0*Rzeta3)

if scheme=='MSRn':
    d1dec=4.0/3.0
    d2dec=13.3398125-1.04136875*nf
    d3dec=188.671875-26.67734375*nf+0.652690625*(nf**2)
    d4dec=0.0039062500*(911588.0-190683.0*nf+11105.0*(nf**2)-173.604*(nf**3))
else: #MSRp
    d1dec=4.0/3.0
    d2dec=13.443375-1.04136875*nf
    d3dec=190.390625-26.65515625*nf+0.652690625*(nf**2)
    d4dec=0.0039062500*(911932.0-190794.0*nf+11109.4*(nf**2)-173.604*(nf**3))

gamR0=d1dec
gamR1=d2dec-2.0*beta0*d1dec
gamR2=d3dec-4.0*beta0*d2dec-2.0*beta1*d1dec
gamR3=d4dec-6.0*beta0*d3dec-4.0*beta1*d2dec-2.0*beta2*d1dec

print 'd1dec=',d1dec
print 'd2dec=',d2dec
print 'd3dec=',d3dec
print 'd4dec=',d4dec
print ''
print 'gamR0=',gamR0
print 'gamR1=',gamR1
print 'gamR2=',gamR2
print 'gamR3=',gamR3
