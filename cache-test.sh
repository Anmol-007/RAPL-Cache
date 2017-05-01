#!/bin/bash
gcc -o cache-benchmark cache-benchmark.c
gcc -o split-file split-file.c
modprobe msr

    echo "Setting 0x0 (No limit) to msr regsiters 0x638 (PP0/Core) 0x640 (PP1/Uncore)"
    wrmsr 0x638 0x0
    wrmsr 0x640 0x0
    exec ./cpuspeed.sh &
    ./cache-benchmark |& tee res-nolimit.dat
    #make dir
    mkdir lim_none
    pkill -f cpuspeed.sh
    paste a.dat b.dat >> cpu_speed.dat
    cp cpu_speed.dat lim_none/
    ./split-file res-nolimit.dat lim_none
    

    echo "Setting 0x38001 (Limit = 125mW) to msr regsiters 0x638 (PP0/Core) 0x640 (PP1/Uncore)"
    wrmsr 0x638 0x38001
    wrmsr 0x640 0x38001
    exec ./cpuspeed.sh &
    ./cache-benchmark |& tee res-125.dat
    pkill -f cpuspeed.sh
    paste a.dat b.dat >> cpu_speed.dat
    cp cpu_speed.dat lim_125/
    #make dir
    mkdir lim_125
    ./split-file res-125.dat lim_125
    
    echo "Setting 0x38002 (Limit = 250mW) to msr regsiters 0x638 (PP0/Core) 0x640 (PP1/Uncore)"
    wrmsr 0x638 0x38002
    wrmsr 0x640 0x38002
    exec ./cpuspeed.sh &
    ./cache-benchmark |& tee res-250.dat
    pkill -f cpuspeed.sh
    paste a.dat b.dat >> cpu_speed.dat
    cp cpu_speed.dat lim_250/
    #make dir
    mkdir lim_250
    ./split-file res-250.dat lim_250
    
    echo "Setting 0x38004 (Limit = 500mW) to msr regsiters 0x638 (PP0/Core) 0x640 (PP1/Uncore)"
    wrmsr 0x638 0x38004
    wrmsr 0x640 0x38004
    exec ./cpuspeed.sh &
    ./cache-benchmark |& tee res-500.dat
    pkill -f cpuspeed.sh 
    paste a.dat b.dat >> cpu_speed.dat
    cp cpu_speed.dat lim_500/
    #make dir
    mkdir lim_500
    ./split-file res-500.dat lim_500

    echo "Setting 0x38008 (Limit 1000mW) to msr regsiters 0x638 (PP0/Core) 0x640 (PP1/Uncore)"
    wrmsr 0x638 0x38008
    wrmsr 0x640 0x38008
    exec ./cpuspeed.sh &
    ./cache-benchmark |& tee res-1000.dati
    pkill -f cpuspeed.sh
    paste a.dat b.dat >> cpu_speed.dat
    cp cpu_speed.dat lim_1000/
    #make dir
    mkdir lim_1000
    ./split-file res-1000.dat lim_1000

    echo "Setting 0x3800c (Limit = 1500mW) to msr regsiters 0x638 (PP0/Core) 0x640 (PP1/Uncore)"
    wrmsr 0x638 0x3800c
    wrmsr 0x640 0x3800c
    exec ./cpuspeed.sh &
    ./cache-benchmark |& tee res-1500.dat
    pkill -f cpuspeed.sh
    paste a.dat b.dat >> cpu_speed.dat
    cp cpu_speed.dat lim_1500/
    #make dir
    mkdir lim_1500
    ./split-file res-1500.dat lim_1500

    echo "Setting 0x38010 (Limit = 2000mW) to msr regsiters 0x638 (PP0/Core) 0x640 (PP1/Uncore)"
    wrmsr 0x638 0x38010
    wrmsr 0x640 0x38010
    exec ./cpuspeed.sh &
    ./cache-benchmark |& tee res-2000.dat
    pkill -f cpuspeed.sh
    paste a.dat b.dat >> cpu_speed.dat
    cp cpu_speed.dat lim_2000/
    #make dir
    mkdir lim_2000
    ./split-file res-2000.dat lim_2000

    echo "Setting 0x38014 (Limit = 2500mW) to msr regsiters 0x638 (PP0/Core) 0x640 (PP1/Uncore)"
    wrmsr 0x638 0x38014
    wrmsr 0x640 0x38014
    exec ./cpuspeed.sh &
    ./cache-benchmark |& tee res-2500.dat
    pkill -f cpuspeed.sh
    paste a.dat b.dat >> cpu_speed.dat
    cp cpu_speed.dat lim_2500/
    #make dir
    mkdir lim_2500
    ./split-file res-2500.dat lim_2500

    echo "Setting 0x38018 (Limit = 3000mW) to msr regsiters 0x638 (PP0/Core) 0x640 (PP1/Uncore)"
    wrmsr 0x638 0x38018
    wrmsr 0x640 0x38018
    exec ./cpuspeed.sh &
    ./cache-benchmark |& tee res-3000.dat
    pkill -f cpuspeed.sh
    paste a.dat b.dat >> cpu_speed.dat
    cp cpu_speed.dat lim_3000/
    #make dir
    mkdir lim_3000
    ./split-file res-3000.dat lim_3000

    echo "Setting 0x3801c (Limit = 3500mW) to msr regsiters 0x638 (PP0/Core) 0x640 (PP1/Uncore)"
    wrmsr 0x638 0x3801c
    wrmsr 0x640 0x3801c
    exec ./cpuspeed.sh &
    ./cache-benchmark |& tee res-3500.dat
    pkill -f cpuspeed.sh
    paste a.dat b.dat >> cpu_speed.dat
    cp cpu_speed.dat lim_3500/
    #make dir
    mkdir lim_3500
    ./split-file res-3500.dat lim_3500

    echo "Setting 0x38020 (Limit = 4000mW) to msr regsiters 0x638 (PP0/Core) 0x640 (PP1/Uncore)"
    wrmsr 0x638 0x38020
    wrmsr 0x640 0x38020
    exec ./cpuspeed.sh &
    ./cache-benchmark |& tee res-4000.dat
    pkill -f cpuspeed.sh
    paste a.dat b.dat >> cpu_speed.dat
    cp cpu_speed.dat lim_4000/
    #make dir
    mkdir lim_4000
    ./split-file res-4000.dat lim_4000

    echo "Setting 0x38024 (Limit = 4500mW) to msr regsiters 0x638 (PP0/Core) 0x640 (PP1/Uncore)"
    wrmsr 0x638 0x38024
    wrmsr 0x640 0x38024
    exec ./cpuspeed.sh &
    ./cache-benchmark |& tee res-4500.dat
    pkill -f cpuspeed.sh
    paste a.dat b.dat >> cpu_speed.dat
    cp cpu_speed.dat lim_4500/
    #make dir
    mkdir lim_4500
    ./split-file res-4500.dat lim_4500

    echo "Setting 0x38028 (Limit = 5000mW) to msr regsiters 0x638 (PP0/Core) 0x640 (PP1/Uncore)"
    wrmsr 0x638 0x38028
    wrmsr 0x640 0x38028
    exec ./cpuspeed.sh &
    ./cache-benchmark |& tee res-5000.dat
    pkill -f cpuspeed.sh
    paste a.dat b.dat >> cpu_speed.dat
    cp cpu_speed.dat lim_5000/
    #make dir
    mkdir lim_5000
    ./split-file res-5000.dat lim_5000

    echo "Setting 0x3802c (Limit = 5500mW) to msr regsiters 0x638 (PP0/Core) 0x640 (PP1/Uncore)"
    wrmsr 0x638 0x3802c
    wrmsr 0x640 0x3802c
    exec ./cpuspeed.sh &
    ./cache-benchmark |& tee res-5500.dat
    pkill -f cpuspeed.sh
    paste a.dat b.dat >> cpu_speed.dat
    cp cpu_speed.dat lim_5500/
    #make dir
    mkdir lim_5500
    ./split-file res-5500.dat lim_5500

    echo "Setting 0x38030 (Limit = 6000mW) to msr regsiters 0x638 (PP0/Core) 0x640 (PP1/Uncore)"
    wrmsr 0x638 0x38030
    wrmsr 0x640 0x38030
    exec ./cpuspeed.sh &
    ./cache-benchmark |& tee res-6000.dat
    pkill -f cpuspeed.sh
    paste a.dat b.dat >> cpu_speed.dat
    cp cpu_speed.dat lim_6000/
    #make dir
    mkdir lim_6000
    ./split-file res-6000.dat lim_6000

    echo "Setting 0x38034 (Limit = 6500mW) to msr regsiters 0x638 (PP0/Core) 0x640 (PP1/Uncore)"
    wrmsr 0x638 0x38034
    wrmsr 0x640 0x38034
    exec ./cpuspeed.sh &
    ./cache-benchmark |& tee res-6500.dat
    pkill -f cpuspeed.sh
    paste a.dat b.dat >> cpu_speed.dat
    cp cpu_speed.dat lim_6500/
    #make dir
    mkdir lim_6500
    ./split-file res-6500.dat lim_6500

    echo "Setting 0x38038 (Limit = 7000mW) to msr regsiters 0x638 (PP0/Core) 0x640 (PP1/Uncore)"
    wrmsr 0x638 0x38038
    wrmsr 0x640 0x38038
    exec ./cpuspeed.sh &
    ./cache-benchmark |& tee res-7000.dat
    pkill -f cpuspeed.sh
    paste a.dat b.dat >> cpu_speed.dat
    cp cpu_speed.dat lim_7000/
    #make dir
    mkdir lim_7000
    ./split-file res-7000.dat lim_7000

    echo "Setting 0x3803c (Limit = 7500mW) to msr regsiters 0x638 (PP0/Core) 0x640 (PP1/Uncore)"
    wrmsr 0x638 0x3803c
    wrmsr 0x640 0x3803c
    exec ./cpuspeed.sh &
    ./cache-benchmark |& tee res-7500.dat
    pkill -f cpuspeed.sh
    paste a.dat b.dat >> cpu_speed.dat
    cp cpu_speed.dat lim_7500/
    #make dir
    mkdir lim_7500
    ./split-file res-7500.dat lim_7500


mkdir ../cache_results
cp -r ./lim* ../cache_results
cp ./res-*.dat  ../cache_results

exec ./cache-latency.sh
sleep 2
pkill -f cache-latency.sh

exec ./backup.sh
sleep 1
pkill -f backup.sh
