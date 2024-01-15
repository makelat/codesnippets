import os

#Overwrite possible previous test.txt (use "w")
f = open("test.txt", "w")
f.write("First line\n")  #Newline not added automatically
f.close()

#Open test.txt for reading ("r")
print("1st time reading test.txt:")
f = open("test.txt", "r")
print(f.read())
f.close()

#Append to test.txt ("a")
f = open("test.txt", "a")
f.write("Second line")  #If opened for 3rd time, would continue writing here
f.close()

#Open test.txt for reading ("r")
print("2nd time reading test.txt:")
f = open("test.txt", "r")
print(f.read())
f.close()

#To prevent cluttering run directory, remove files/dirs like this
filename="test.txt"
if not os.path.exists("testdir"):
    os.mkdir("testdir")
if os.path.exists("testdir/"+filename):
    os.remove("testdir/"+filename)
else:
    print("Cannot remove "+filename)
    
#Removing _empty_ directories (think shell) would work with:
#os.rmdir("dirname")
