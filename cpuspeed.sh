#!/bin/bash

echo "#Data of CPU Clock Frequency" > cpu_speed.dat
echo "#Sr No" > a.dat
echo "CPU Speed" > b.dat
i=0

while [ 0 -lt 1 ]
do
    echo "$i" >> a.dat 
    cat /sys/devices/system/cpu/cpu0/cpufreq/cpuinfo_cur_freq >> b.dat
    sleep 1
    i=`expr $i + 1`
done
paste a.dat b.dat >> cpu_speed.dat
    

