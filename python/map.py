#N.B. the python map is not an entity like a C++ map, but a
#way to apply a function to a set of input values "easily"
#Example: apply this function:
def func(a):
    return 2*a
#...to this list of input values:
vec=[1,3,7]
mapret = map(func,vec)  #Returns a strange object that must be 
print(list(mapret))     #...converted to a list for print

#The NEAR-EQUIVALENT OF A C++ MAP is a dictionary:
d = {}                      #No magic in initialization
d["shinigamis"] = {"Ryuk"}  #However, all keys and
d["apples"] = 1337          #...values don't need to
d[42] = "the answer"        #...have the same type
print("Shinigamis in dictionary: ",d["shinigamis"])
print("Number of apples: ",d["apples"])
print("42 = ",d[42])
