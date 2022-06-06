#!/bin/sh
DIR=$1
echo Generate Project: $DIR
if [ -d "$DIR" ]; then 
  rm $1 -R; 
fi
if [ ! -d "$DIR" ]; then
  mkdir $1;
fi
cd $1
cmake -G "Ninja" -DTARGET=pc ../.. 
echo Compile ...
ninja
cd ../../../../../
