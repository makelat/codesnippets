#Illustrates possibilities for including more than one parameter in multiprocessing pool.
#Multiple arbitrary numbers can be included by making the pool input array higher rank, 
#here the focus is on other params e.g. flags and strings
from functools import partial
from itertools import repeat
from multiprocessing import Pool, freeze_support
from os import cpu_count

def func(a, b=0,msg=""):
    print(msg)
    return a + b

def main():
    inputVec = range(10)
    same4all = 1
    same4all1 = "かがりさんは神様の声を聞けます。"
    procs = Pool(processes=cpu_count())
    #Usual pool usage for inputVec, the remaining parameters are the same for all threads
    ret1 = procs.starmap(func, zip(inputVec, repeat(same4all), repeat(same4all1)))
    ret2 = procs.map(partial(func, b=same4all, msg=same4all1), inputVec)  #ALT, same result^
    assert ret1 == ret2
    print('ret1 = ',ret1)
    print('ret2 = ',ret2)

if __name__=="__main__":
    freeze_support()
    main()
