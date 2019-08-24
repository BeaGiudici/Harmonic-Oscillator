#!/bin/bash

echo 'CASE a = 2'
sed "s|@n|32|g;s|@m|0.5|g;s|@w|2.0|g" ../../include/global-gen.h > ../../include/global.h
make times > garbage.txt
echo "{" >> ../../results/times.json
./times >> ../../results/times.json
echo "}," >> ../../results/times.json

echo 'CASE a = 1'
sed "s|@n|64|g;s|@m|1.0|g;s|@w|1.0|g" ../../include/global-gen.h > ../../include/global.h
make times > garbage.txt
echo "{" >> ../../results/times.json
./times >> ../../results/times.json
echo "}," >> ../../results/times.json

echo 'CASE a = 0.5'
sed "s|@n|128|g;s|@m|2.0|g;s|@w|0.5|g" ../../include/global-gen.h > ../../include/global.h
make times > garbage.txt
echo "{" >> ../../results/times.json
./times >> ../../results/times.json
echo "}," >> ../../results/times.json

echo 'CASE a = 0.25'
sed "s|@n|256|g;s|@m|4.0|g;s|@w|0.25|g" ../../include/global-gen.h > ../../include/global.h
make times > garbage.txt
echo "{" >> ../../results/times.json
./times >> ../../results/times.json
echo "}" >> ../../results/times.json
