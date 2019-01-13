#!/bin/sh
set -x
s="the quick brown fox jumps"
r="aeiou"
./remchar "$s" $r
