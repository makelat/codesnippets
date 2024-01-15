### PSEUDODATA

#We simply generate Nreq points that can be classified into two groups:
#those above and below the y=x line, within some tolerance tol
#The groups are made more (less) distinct for the training (test) dataset,
#So that when testing, a simple fit to the training set will likely not classify
#the entire test set correctly, although by construction (y=x line) also the 
#test set will (artficially) be possible to separate linearly.
def generatePoints(Nreq,tol,label):
    Ngen=0
    X=[]
    y=[]
    while Ngen < Nreq:
        crds = np.random.rand(2)
        #Drop all points w/ x=y in some tolerance for training set
        if crds[0] < crds[1]+tol and crds[0] > crds[1]-tol:
            if 'train' in label: continue
            #For test set, drop only half the points near boundary
            elif np.random.rand(1)[0] > 0.5: continue
        X.append([crds[0],crds[1]])
        if crds[0] > crds[1]:
            y.append(1.0) 
        else: y.append(-1.0)
        Ngen += 1
    
    fX = open('X_'+label+'.dat', "w")
    fy = open('y_'+label+'.dat', "w")
    for Xi,yi in zip(X,y):
        fX.write(str(Xi[0])+'    '+str(Xi[1])+'\n')
        fy.write(str(yi)+'\n')
    fX.close()
    fy.close()

generatePoints(Nreq=1000,tol=0.1,label='train')
generatePoints(Nreq=2000,tol=0.05,label='test')
