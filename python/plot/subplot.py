import matplotlib.pyplot as plt
import numpy as np

def add_subplot_axes(ax,rect):
    fig=plt.gcf()
    pos=fig.transFigure.inverted().transform(ax.transAxes.transform(rect[0:2]))    
    box = ax.get_position()
    w = rect[2]*box.width
    h = rect[3]*box.height
    subax = fig.add_axes([pos[0],pos[1],w,h],axisbg='w')
    #Style setup
    lblsize = subax.get_xticklabels()[0].get_size(),\
              subax.get_yticklabels()[0].get_size()
    subax.xaxis.set_tick_params(labelsize=lblsize[0])
    subax.yaxis.set_tick_params(labelsize=lblsize[1])
    return subax

if __name__ == '__main__':

    #A few graphs to plot
    x=np.linspace(0,2,20)
    data1 = [x,x**2]
    data2 = [[0,0.7],[0.5,0.5]]
    
    #Main plot
    fig = plt.figure(figsize=(6,6))
    plt.plot(data1[0],data1[1],color='dodgerblue')
    plt.plot(data2[0],data2[1],color='salmon')
    lbl=["x","y"]
    plt.xlabel(lbl[0])
    plt.ylabel(lbl[1])
    
    #Add a zoomed-in region as a subplot
    ax = fig.add_subplot(111)
    x0,y0 = 0.13,0.5  #Fraction of x and y axes to start subplot at
    xw,yw = 0.5,0.4  #Subplot width along x and y axes    
    ax1 = add_subplot_axes(ax,[x0,y0,xw,yw])
    ax1.plot(data1[0],data1[1],color='dodgerblue')
    ax1.plot(data2[0],data2[1],color='salmon')
    ax1.set_xlim(0,1)
    ax1.set_ylim(0,1)
    ax1.set_xlabel(lbl[0])
    ax1.set_ylabel(lbl[1])

    plt.savefig('subplot.pdf')
