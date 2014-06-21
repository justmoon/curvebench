#!/bin/sh

for i in /sys/devices/system/node/node0/cpu*/online
do
  echo 0 > $i
done

for i in /sys/devices/system/cpu/cpu*/cpufreq
do
  echo performance > $i/scaling_governor
done
