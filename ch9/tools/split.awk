#!/usr/bin/env awk -f
# split.awk: split input into one word per line

{ for (i = 1; i <= NF; i++ ) print $i }
