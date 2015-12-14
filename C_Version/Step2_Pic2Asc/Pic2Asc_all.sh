#!/bin/bash

function Usage(){
    echo ""
    echo "Usage:"
    echo "./Pic2Asc_all.sh dirName targetFileName"
    echo ""
    echo "dirName is the directory which contains all the pictures you want to transform."
    echo "targetFileName is the text file which save the result(ASCII characters)."
    echo ""
}

if [ $# -lt "2" ] ; then
    Usage
    exit 0
fi

for eachPic in `ls $1`
do
    ./Pic2Asc $1/$eachPic $2
    echo "$eachPic done!"
done
