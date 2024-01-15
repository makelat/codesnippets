import time
from multiprocessing import Process

def printer(threadid,val):
    time.sleep(threadid)  #Sleep for threadid seconds
    print str(threadid)+": "+val

if __name__ == '__main__':
    strs = ["shinigami","wa","ringo","ga","daisuki"]

    start_time = time.time()

    #W/ multithreading: prints strings 1s after one another
    p=[]
    for i in range(len(strs)):
        p.append(Process(target=printer, args=(i,strs[i],)))
        p[-1].start()
    for i in range(len(strs)):
        p[i].join()

    #W/o/ multithreading: increasing delay between prints
    for i in range(len(strs)):
        printer(i,strs[i])
    
