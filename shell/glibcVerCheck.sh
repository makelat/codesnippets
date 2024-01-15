#!/bin/bash

minver=2.30
glibcver=`ldd --version | awk '{if (NR==1) print $NF}'`
echo "Found GLIBC version "${glibcver}
if [[ $glibcver > $minver ||  $glibcver == $minver ]]
then
    echo "...version is sufficient"
else
    echo "...version is insufficient!"
fi
