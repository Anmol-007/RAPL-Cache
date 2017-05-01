#!/bin/bash
gcc -o cache-benchmark cache-benchmark.c
gcc -o split-file split-file.c
modprobe msr

declare -a fname=(none 125 250 375 500 625 750 875 1000 1125 1250 1375 1500 1625 1750 1875 2000 2125 2250 2375 2500 2625 2750 2875 3000 3125 3250 3375 3500 3625 3750 3875 4000 4500 5000 5500 6000 6500 7000 7500 8000 8500 9000 9500)
i=0
for limit in 0x0 0x78001 0x78002 0x78003 0x78004 0x78005 0x78006 0x78007 0x78008 0x78009 0x7800a 0x7800b 0x7800c 0x7800d 0x7800e 0x7800f 0x78010 0x78011 0x78012 0x78013 0x78014 0x78015 0x78016 0x78017 0x78018 0x78019 0x7801a 0x7801b 0x7801c 0x7801d 0x7801e 0x7801f 0x78020 0x78024 0x78028 0x7802c 0x78030 0x78034 0x78038 0x7803c 0x78040 0x78044 0x78048 0x7804c
do
    echo "Setting $limit to msr regsiters 0x638 (PP0/Core) 0x640 (PP1/Uncore)"
    wrmsr 0x638 $limit
    wrmsr 0x640 $limit

    exec ./cpuspeed.sh &
    ./cache-benchmark |& tee res-"${fname[$i]}".dat
    #make dir
    mkdir lim_"${fname[$i]}"
    pkill -f cpuspeed.sh
    paste a.dat b.dat >> cpu_speed.dat
    cp cpu_speed.dat lim_"${fname[$i]}"/
    ./split-file res-"${fname[$i]}".dat lim_"${fname[$i]}"
    i=`expr $i+1`
done

mkdir ../cache_results
cp -r ./lim* ../cache_results
cp ./res-*.dat  ../cache_results

exec ./cache-latency.sh
sleep 2
pkill -f cache-latency.sh

exec ./backup.sh
sleep 1
pkill -f backup.sh
