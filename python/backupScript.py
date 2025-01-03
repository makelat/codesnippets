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
#Param  srcdir  The source file direcory to be copied
#       tgtdir  The destination to copy to
#       hardcp  Set to True if links are to be followed and hard copies taken
def copyRecursion(srcdir,tgtdir,hardcp=False):

    #Skip directories that are actually symlinks if hard copies not requested
    #N.B. islink does not return expected outcome if terminating character is '/'!
    #The soft links are copied below by copy2, treated as single files
    if os.path.islink(srcdir[:-1]) and not hardcp: return True

    #If no target exists, simply copy the source using shutil
    #Note that shutil requires that the target/destination does not exist
    if not os.path.exists(tgtdir):
        shutil.copytree(src=srcdir,dst=tgtdir,symlinks=not hardcp,\
                        copy_function=copy2,ignore=None)
        print("Copied "+tgtdir+" using copytree")
        return True

    for item in os.listdir(srcdir):

        #Copy subdirectory contents recursively
        if os.path.isdir(srcdir+item):
            copyRecursion(srcdir+item+"/",tgtdir+item+"/",hardcp=hardcp)

        #If file exists in target, check modification date and copy newer files
        if not os.path.exists(tgtdir+item) or isNewer(srcdir+item,tgtdir+item):
            shutil.copy2(srcdir+item,tgtdir+item,follow_symlinks=hardcp)
            print("Copied to "+tgtdir+item)
    
    return True

if __name__=="__main__":

    # BEGIN user input

    #Specify source and target locations. Defaults assume Ubuntu paths.
    #Copy files from here...
    srcpath="/home/user/"
    #...to here. Recommend replacing exthdd (laptop) by drive (computer) name
    tgtpath="/media/user/exthdd/laptop/"

    #Specify directories to copy, e.g. ["Documents","Pictures"]
    cpdirs = ["Desktop",\
              "Documents",\
              "Downloads",\
              "Music",\
              "Pictures"]
    
    hardcp=False  #Follow symlinks and back them up as hard copies?

    # END user input

    #Loop through the subdirectories to be copied
    for cpdir in cpdirs:
        if cpdir[-1]!='/': cpdir+='/'  #Ensure path formatting

        #Ensure target exists
        if not os.path.exists(tgtpath):
            try: os.mkdir(tgtpath)
            except: print("Cannot init target path "+tgtpath)

        #Copy files and directories recursively
        try: copyRecursion(srcdir=srcpath+cpdir,tgtdir=tgtpath+cpdir,hardcp=hardcp)
        except: print("Could not copy source "+srcpath+cpdir+" to "+tgtpath+cpdir)

