#This script illustrates setting up a list of running many ROOT macros one after
#another without needing any user commands in between.

CERNBOX=1
T=1	#True
F=0	#False (redundant here, for ref.)
PATH2CB=/home/user/cernbox

echo "Running writeToFile1"
cp writeToFile1.C nowRunning.C
root nowRunning.C -l -q
if [ $CERNBOX == $T ]
then
    mv out.txt $PATH2CB/out1.txt
else
    mv out.txt out1.txt
fi

echo "Running writeToFile2"
cp writeToFile2.C nowRunning.C
root nowRunning.C -l -q
if [ $CERNBOX == $T ]
then
    mv out.txt $PATH2CB/out2.txt
else
    mv out.txt out2.txt
fi

#Remove the dummy "main" to be run
rm nowRunning.C

echo "Done."

