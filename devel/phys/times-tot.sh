#!/bin/bash

echo "[" > ../../results/times.json

make clean

for (( i = 1 ; i <= 10 ; i += 1 )) ; do
     echo "Loop number $i"
     . ./times-single.sh
     if [[ $i != 10 ]] ; then
          echo "," >> ../../results/times.json
     fi
done

echo "]" >> ../../results/times.json
rm garbage.txt
make clean

cd ../../fit
python3 times.py
cd ..
