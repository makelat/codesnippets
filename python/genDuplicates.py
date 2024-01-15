import numpy as np

#List of generators: 1st col for light contribution, 2nd for charm
gens = [ ['SIBYLL','QGSJET'             ],\
         ['SIBYLL','NLOFF_YUSEON'       ],\
         ['SIBYLL','KTsaturationP8_ANNA'],\
         ['DPMJET','KTsaturationP8_ANNA'],\
         ['SIBYLL','NLOFF_YUSEON'       ]  ]

#Alternatively, legacy codes only list light-only or charm-only
#Current implementation supports the below simple list as well
#gens = ['SIBYLL',\
#        'KTsaturationP8_ANNA',\
#        'NLOFF_YUSEON',\
#        'NLOFF_YUSEON']

Ng=len(gens)

dupgens=[]

#Force array form in case gens has rank<2
if np.array(gens[0]).ndim==0:
    gensarr = np.array([[g] for g in gens])
else:
    gensarr = np.array(gens)
    
for iptype in range(len(gensarr[0])):
    ptypegens, readgens, iptypeduplicates = [],[],[]
    ptypegens = gensarr[1:,iptype]
    for iptypegen,ptypegen in enumerate(ptypegens):
        if ptypegen not in readgens:
            readgens.append(ptypegen)
            iduplicates=[] 
            for iptypegen2,ptypegen2 in enumerate(ptypegens[1+iptypegen:]):
                if ptypegen == ptypegen2:
                    if len(iduplicates)==0:
                        iduplicates.append(iptypegen)
                    iduplicates.append(iptypegen2+1+iptypegen)
            if len(iduplicates)>0:
                iptypeduplicates.append(iduplicates)
    dupgens.append(iptypeduplicates)

#Now dupgens 1st index retrieves light or charm lists, whose elements 
#are lists of the >1 indices of the generators that appear multiple times,
#s.t. all lambdas w/ those indices (in light or charm case, respectively)
#can be replaced with the lambda corresponding to the first entry. 
#Also in the infomatrix, remove rows & cols of the redundant indices
#E.g. if the output is 
#    [[[0, 1, 3]], [[0, 3], [1, 2]]]
#remove 1st and 3rd (starting from 0) lines/cols from the pion and kaon
#submatrices, and lines/cols 3 and 2 from the charm submatrix
print(dupgens)

#Check number of independent gens in light and charm sectors
for isec in range(len(gensarr[0])):
    indeps=[]
    for g in gensarr[1:,isec]:
        if g not in indeps:
            indeps.append(g)
    print('Sector ',isec,' has ',len(indeps),' independent generators:')
    print(indeps)
