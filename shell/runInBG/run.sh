#A script to test running a program in background
#USAGE:
# chmod +x run.sh
# ./run.sh > log.txt &
#In the above command, "&" is an instruction to run in background. 
#If the program was finished successfully, log.txt will contain the line "Done"

echo "Starting script"
g++ -o runInBG main.C
echo "Compiled. Proceeding to run."
./runInBG
echo "Removing jargon. Will produce file finished.txt when ready"
rm out.txt
echo "Done"
