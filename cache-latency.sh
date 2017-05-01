#!/bin/bash
gcc -o  get-results get-results.c
echo "#Sr   Limit       L1 Hit  L2 hit  L3 Hit  Memory" > cache-stat.dat
echo "1	dummy 	0.00		0.33		0.69" >> cache-stat.dat

echo "#Sr   Limit       L2/L1   L3/L2   Mem/L3" > cache-ratio.dat
echo "1	dummy 	3.00		5.33		10.69" >> cache-ratio.dat

echo "#Sr   Limit       %L1     %L2     %L3     %Mem" > cache-percent.dat
echo "1	dummy 	0		0		0" >> cache-percent.dat

for file in `ls -vrd lim*`
do
	echo $file
	./get-results $file
done
#./get-results lim_none
#./get-results lim_9500 
#./get-results lim_9000 
#./get-results lim_8500
#./get-results lim_8000 
#./get-results lim_7500 
#./get-results lim_7000 
#./get-results lim_6500 
#./get-results lim_6000 
#./get-results lim_5500 
#./get-results lim_5000 
#./get-results lim_4500 
#./get-results lim_4000 
#./get-results lim_3500 
#./get-results lim_3000 
#./get-results lim_2500 
#./get-results lim_2000 
#./get-results lim_1500 
#./get-results lim_1000 
#./get-results lim_500
#./get-results lim_250 
#./get-results lim_125  
#
./plot-cache-percent.pg > percent.jpg
./plot-cache-ratio.pg > results-ratio.jpg
./plot-cache-stat.pg > results-stat.jpg
./plot-mem-stat.pg > results-mem.jpg

cp -r *cache*.dat  ../cache_results/
cp -r *.jpg ../cache_results/
