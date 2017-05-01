#!/bin/bash

fname="cache-results"
N=1
# Increment $N as long as a directory with that name exists
while [[ -d "/home/pari/Backup/$fname-$N" ]] ; do
    N=$(($N+1))
done

mkdir "/home/pari/Backup/$fname-$N"
cp -r ../cache_results/* /home/pari/Backup/$fname-$N/
