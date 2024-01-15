#!/bin/bash

#This script is the "main" program here.
#Illustrate compiling and executing a program via script
#
#For example, call program "hello", w/ argument "こんばんは！", output to "printout.log":
#
#  ./compileAndRun.sh -p hello -a "こんばんは！" -o printout.log

#Parse input flags and arguments given to this main script
while getopts p:a:o: arg
do
    case "${arg}" in
        p) progname=${OPTARG};;
        a) progarg=${OPTARG};;
        o) outname=${OPTARG};;
    esac
done

#Check that requested program exists, proceed to compile and run
if [ -e ${progname}.cxx ]
then
    echo "Compiling and executing program ${progname}, output to printout.log"
    g++ --std=gnu++0x -o ${progname} ${progname}.cxx
    ./${progname} ${progarg} >> printout.log
else
    echo "Program ${progname} not found"
fi
