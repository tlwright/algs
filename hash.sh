#!/bin/sh
#set -x
lim=$((5 + $RANDOM % 10))
cnt=0
cmd=./hash
while [ $cnt -lt $lim ]; do
    cmd="$cmd $(($RANDOM % 10))"
    cnt=$(($cnt + 1))
done
set -x
eval $cmd
