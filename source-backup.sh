#!/bin/bash

DATE=$(date +"%d%m%Y")
N=1

# Increment $N as long as a directory with that name exists
while [[ -d "/home/anmol-panda/Documents/Backup/cache_benchmark/$DATE-$N" ]] ; do
    N=$(($N+1))
done

mkdir "/home/anmol-panda/Documents/Backup/cache_benchmark/$DATE-$N"
cp -r ./*  /home/anmol-panda/Documents/Backup/$DATE-$N/
