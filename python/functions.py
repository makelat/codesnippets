#Run using python3 functions.py

def myFunc0():
    print("皆さん今日は！パイトンです。")  #Special characters need python3

def myFunc1(x):
    print('Input:',x)

#Function with arbitrarily many arguments:
def myFunc2(*parlist):
    print('Input:')
    for x in parlist:
        print(x)

#Call functions    
myFunc0()
myFunc1("1")
myFunc1(1/137)
myFunc2("test","several args",1.37,137)

#Lambda functions
lMultiplier = lambda a, b : a*b
print(lMultiplier(10,137))
