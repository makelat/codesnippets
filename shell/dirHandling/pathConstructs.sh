#!/bin/bash
#Illustrates a possible structure for a schell script performing operations in select subdirectories of a list of main directories. Helpful when both have many directories, but not all should be operated on.
#Here we simply construct the paths appropriately and print a log file, but the echos could be replaced by virtually any bash command to be performed in the subdirectories.
declare -a mainDirs=("main1" "main2")

rm log.txt  #Clean old file if there

for mainDir in ${mainDirs[@]}; do

    echo "Declaring arays for..."
    if [[ "${mainDir}" == "main1" ]]; then
        echo ${mainDir}
        declare -a firstDirs=("A" "C")
        declare -a secondDirs=("A")
    fi
    if [[ "${mainDir}" == "main2" ]]; then
        echo ${mainDir}
        declare -a firstDirs=("A" "B" "C")
        declare -a secondDirs=("A" "B" "C")
    fi

    #With only statistical uncertainties
    echo "About to work on firstDirs"
    for subDir in ${firstDirs[@]}; do
        name="first"
        echo ${mainDir}/${name}/${subDir} >> log.txt
    done

    #With only statistical uncertainties
    echo "About to work on secondDirs"
    for subDir in ${secondDirs[@]}; do
        name="second"
        echo ${mainDir}/${name}/${subDir}/${xFrunFile} >> log.txt
    done
    
done
