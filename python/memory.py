#Illustrating that variables defined inside functions are not stored in memory

#Here, x is always accessible in the memory, as it is a global variable
x=1
x+=1
print("x=",x)

#Here, y is defined inside the function
def func(val):
    y=val
    y+=1
    print("y=",y)

#Now let's call func, "y" in principle gets defined...
func(1)
#...but we cannot call "y" outside of the function
print("y=",y)

#Sometimes the objects required for a single computation, and never afterwards,
#can be large. Therefore, it is advisable to implement functionality inside functions, 
#and then call those functions similar to how "main" works in C.
