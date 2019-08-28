#!/bin/bash

cd ..
echo "[" > results/cont_limit.json

cd fit/
for((i=32; i<=512; i=i*2)); do
     python3 single_fit.py ../results/deltaE_$i.dat ../results/matrix_el_$i.dat
     case $i in
     128)
          python3 single_fit.py ../results/deltaE_160.dat ../results/matrix_el_160.dat;;
     256)
          python3 single_fit.py ../results/deltaE_320.dat ../results/matrix_el_320.dat;;
     esac
done
echo "]" >> ../results/cont_limit.json

python3 total_fit.py > ../results/continuum.dat
python3 times.py > ../results/final_times.dat
cd ..
