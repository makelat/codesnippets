#A quick/simple Python script illustrating os and shutil features
#for backing up files into e.g. an external hard drive
#The user should only need to modify the path/dir names in the main function

#The script is intended for simple demo cases, use and modify at your own risk.

#Importing required modules
import os
import shutil

#Check if last modification date of src is more recent than that of tgt
def isNewer(src,tgt):
    return os.path.getmtime(src) > os.path.getmtime(tgt)

#Recursive function to copy files in a (sub)directory
def copyRecursion(srcdir,tgtdir):

    #If no target exists, simply copy the source using shutil
    #Note that shutil requires that the target/destination does not exist
    if not os.path.exists(tgtdir):
        shutil.copytree(src=srcdir,dst=tgtdir,symlinks=False,ignore=None)

    for item in os.listdir(srcdir):

        #Copy subdirectory contents recursively
        if os.path.isdir(srcdir+item):
            copyRecursion(srcdir+item+"/",tgtdir+item+"/")

        #If file exists in target, check modification date and copy newer files
        #However, don't files replaced by links
        if not os.path.exists(tgtdir+item) or isNewer(srcdir+item,tgtdir+item):
            if os.path.islink(srcdir+item): continue  #Skip links
            shutil.copy(srcdir+item,tgtdir+item)
            print("Copied "+tgtdir+item)

if __name__=="__main__":

    # BEGIN user input

    #Specify source and target locations. Defaults assume Ubuntu paths.
    #Copy files from here...
    srcpath="/home/user/"
    #...to here. Recommend replacing exthdd (laptop) by drive (computer) name
    tgtpath="/media/user/exthdd/laptop/"

    #Specify directories to copy, e.g. ["Documents","Pictures"]
    cpdirs = ["Desktop",\
              "Documents/",\
              "Downloads/",\
              "Music/",\
              "Pictures",\
             ]

    # END user input

    #Loop through the subdirectories to be copied
    for cpdir in cpdirs:
        if cpdir[-1]!='/': cpdir+='/'  #Ensure path formatting

        #Ensure target exists
        if not os.path.exists(tgtpath):
            try: os.mkdir(tgtpath)
            except: print("Cannot init target path "+tgtpath)

        #Copy files and directories recursively
        try: copyRecursion(srcdir=srcpath+cpdir,tgtdir=tgtpath+cpdir)
        except: print("Could not copy source "+srcpath+cpdir)

