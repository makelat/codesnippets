#!/bin/bash

declare -i n=0
declare -i m=0
declare -i l=0

for dir in */ ; do
    if [[ ! -e $dir/finished.txt ]]
    then
        echo "$dir unfinished"
        m=$(( m + 1 ))
    fi
    n=$(( n + 1 ))
done

l=$(( n - m ))
echo "$l / $n finished"
