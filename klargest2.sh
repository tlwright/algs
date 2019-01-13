#!/bin/sh
#set -x
lim=$((5 + $RANDOM % 10))
cnt=0
item=$(($RANDOM % 10))
cmd="./klargest2 $item "
arg=$(($RANDOM % 10))
while [ $cnt -lt $lim ]; do
    cmd="$cmd $arg"
    arg=$(($arg + $RANDOM % 10))
    cnt=$(($cnt + 1))
done
set -x
eval $cmd
