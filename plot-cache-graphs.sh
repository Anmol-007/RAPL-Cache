#!/usr/bin
exec ./plot-cache-ratio.pg > results.jpg
sleep 1
pkill -f plot-cache-ratio.pg

