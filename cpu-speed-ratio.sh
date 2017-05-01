#!/bin/bash
echo -e "#SrNo\tlimit\t\tcpu-speed-ratio to min CPU speed" > cpu-speed-ratio.dat
echo -e "0:dummy:1" >> cpu-speed-ratio.dat 
 
declare -a lim=( 125 250 500 1000 1500 2000 2500 3000 3500 4000 4500 5000 5500 6000 6500 7000 7500 8000 8500 9000 9500 none)
i=21
cpu_speed_unb=$(awk '{ total += $2 } END { printf("%.f\n", total/NR) }' lim_none/cpu_speed.dat) 
for f in `ls -vr lim*/cpu_speed.dat`; do
        #echo "$f"
        cpu_speed="$(awk '{ total += $2 } END { printf("%.f\n", total/NR) }' $f)"
        #echo ${lim[$i]}"="$cpu_speed" unb="$cpu_speed_unb
        #cpu_speed=$(echo "scale=2 ; $cpu_speed / $cpu_speed_unb" | bc)
        cpu_speed="$(echo "scale=2; ($cpu_speed_unb/$cpu_speed)" | bc)"
        echo $cpu_speed
        echo -e $i ":" ${lim[$i]} ":"$cpu_speed >> cpu-speed-ratio.dat 
        i=`expr $i - 1`
done
