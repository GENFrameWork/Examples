#!/bin/sh
echo Generate Project ...
rm $1 -R
mkdir $1
cd $1
cmake -G "Ninja" -DTARGET=pc ../..
echo Compile ...
ninja
cd ../../../../../
