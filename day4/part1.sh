#!/usr/bin/env bash

infile="$1"

sumline=" 0"

while read r
do
    sumline="$(echo "2 ^ ($(echo "$r" | cut -d: -f2 | tr -d '|' | tr ' ' '\n' | grep -Ev '^ *$' | sort -n | uniq -c | grep -c '^ *2 ') - 1)" | bc) + $sumline"
done < $infile
echo "Result: $(echo $sumline | bc)"
