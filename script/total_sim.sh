#!/bin/bash

cd ..
echo "[" > results/times.json

cd main
make clean

echo 'CASE a = 2'
sed "s|@n|32|g;s|@m|0.5|g;s|@w|2.0|g" ../include/global-gen.h > ../include/global.h
make binning jackknife > garbage.dat
echo "{" >> ../results/times.json
./binning >> ../results/times.json
echo "}," >> ../results/times.json
./jackknife
mv ../results/deltaE.dat ../results/deltaE_32.dat
mv ../results/matrix_el.dat ../results/matrix_el_32.dat

echo 'CASE a = 1'
sed "s|@n|64|g;s|@m|1.0|g;s|@w|1.0|g" ../include/global-gen.h > ../include/global.h
make binning jackknife > garbage.dat
echo "{" >> ../results/times.json
./binning >> ../results/times.json
echo "}," >> ../results/times.json
./jackknife
mv ../results/deltaE.dat ../results/deltaE_64.dat
mv ../results/matrix_el.dat ../results/matrix_el_64.dat

echo 'CASE a = 0.5'
sed "s|@n|128|g;s|@m|2.0|g;s|@w|0.5|g" ../include/global-gen.h > ../include/global.h
make binning jackknife > garbage.dat
echo "{" >> ../results/times.json
./binning >> ../results/times.json
echo "}," >> ../results/times.json
./jackknife
mv ../results/deltaE.dat ../results/deltaE_128.dat
mv ../results/matrix_el.dat ../results/matrix_el_128.dat

echo 'CASE a = 0.25'
sed "s|@n|256|g;s|@m|4.0|g;s|@w|0.25|g" ../include/global-gen.h > ../include/global.h
make binning jackknife > garbage.dat
echo "{" >> ../results/times.json
./binning >> ../results/times.json
echo "}," >> ../results/times.json
./jackknife
mv ../results/deltaE.dat ../results/deltaE_256.dat
mv ../results/matrix_el.dat ../results/matrix_el_256.dat

echo 'CASE a = 0.2'
sed "s|@n|320|g;s|@m|5.0|g;s|@w|0.2|g" ../include/global-gen.h > ../include/global.h
make binning jackknife > garbage.dat
echo "{" >> ../results/times.json
./binning >> ../results/times.json
echo "}," >> ../results/times.json
./jackknife
mv ../results/deltaE.dat ../results/deltaE_320.dat
mv ../results/matrix_el.dat ../results/matrix_el_320.dat

echo 'CASE a = 0.125'
sed "s|@n|512|g;s|@m|8.0|g;s|@w|0.125|g" ../include/global-gen.h > ../include/global.h
make binning jackknife > garbage.dat
echo "{" >> ../results/times.json
./binning >> ../results/times.json
echo "}" >> ../results/times.json
./jackknife
mv ../results/deltaE.dat ../results/deltaE_512.dat
mv ../results/matrix_el.dat ../results/matrix_el_512.dat

echo "]" >> ../results/times.json
rm garbage.dat
make clean

echo 'FIT'
cd ../script
. ./fit.sh

