import time
import multiprocessing
import numpy as np
from multiprocessing import Process


def a_function(in_value,ret_bool,ret_value,ret_array,ret_array_size):
    
    # BEGIN simple example to illustrate converting "multiprocessing" 
    #ret value data types to regular values, and back; this allows
    #easy single vs multiprocessing program conversions/checks
    retbool = ret_bool.value
    if retbool:
        print("Before a_function: retbool=True")
    else:
        print("Before a_function: retbool=False")
    retbool=True
    ret_bool.value = retbool
    # END
    
    # BEGIN an example of manipulating the return values and arrays
    retval = 137*in_value
    ret_value.value = retval
    Nentries = 10
    #if Nentries>arrmax: TODO check sth like this if max size not well-known
    #    print('You are trying to return a too large array')
    #    Nentries=arrmax
    for i in range(Nentries):
        ret_array[i] = i*retval #Filling first elements of a presized array
    ret_array_size.value = Nentries
    # END
#a_function

if __name__ == '__main__':
    in_value=1.
    arrmax=100  #Max size of array to be returned by process
    #Init processes
    ret_bool  = multiprocessing.Value("b", False, lock=False)
    ret_value = multiprocessing.Value("d", 0.0, lock=False)
    ret_array = multiprocessing.Array("d", range(arrmax))  #Size must be given
    ret_array_size = multiprocessing.Value("i", 0, lock=False)
    p=[]
    Np = 1 #Number of processes (~threads)
    #TODO for the example to be truly useful, should handle storing the multiple 
    #     return vectors and access them afterwards
    for i in range(Np):
        p.append(multiprocessing.Process(target=a_function,\
                                         args=[in_value,\
                                               ret_bool,\
                                               ret_value,\
                                               ret_array,ret_array_size]))
        p[-1].start()
    #Join threads
    for i in range(Np):
        p[i].join()

    print("In: "+str(in_value)+", out: "+str(ret_value.value))
    for ix in range(ret_array_size.value):
        print(ret_array[ix])

    if ret_bool:
        print("After a_function: ret_bool=True")
    else:
        print("After a_function: ret_bool=False")
