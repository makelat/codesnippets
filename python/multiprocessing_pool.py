from multiprocessing import Pool, cpu_count # A helper function that determines how many cores you have

# Find out how many cpus you have
num_cpus = cpu_count()
print('NCPU available = ',num_cpus)

#num_cpus = 10 #Let's try too many cpus -- Turned out OK

# Make a dummy function that we can send to the workers in the pool
# Returns a sum of val with itself, however that is defined for val
def printer(val):
    step=0
    #Something that takes actual "computing time", so you can check 
    #in system monitor shows that all cpus are actually working
    for i in range(10**8): 
        step+=1
    print('The input is: ', val)
    return val+val

# Make the pool object
p = Pool(processes=num_cpus)
# Make some input to map out to the workers
nums_to_print = range(num_cpus)
M = [[i*10+j for j in range(num_cpus)] for i in range(num_cpus)]

print('\n*** EXAMPLE 1: input is a matrix, each thread is assigned a column ***\n')

#Synchronous exectuion, later code inexecutable before all workers ready
#results = p.map(printer, nums_to_print)
results = p.map(printer, M)

#The asynchronous version has some further features.
#results = p.map_async(printer, nums_to_print)
#print('Results ready = ',results.ready())  #True if all workers finished
#print(results.successful())  #True if all workers successful
# To actually retrieve the result from the async result object, use get
#results = results.get()

print('\nEx.1 results = ')
print(results,'\n')


print('\n*** EXAMPLE 2: each thread is assigned the same matrix ***\n')

usecpus=3 #Don't use all cpus, simple output is easy to print

p2 = Pool(processes=usecpus)
M2 = [[i*10+j for j in range(usecpus)] for i in range(usecpus)]


#Synchronous exectuion, later code inexecutable before all workers ready
results2 = p2.map(printer, [M2 for _ in range(usecpus)])

for i in range(len(results2)):
    print('\nEx.2 results[',i,'] = ')
    print(results2[i],'\n')

print('Original input object remains unmodified:')
print(M2)
