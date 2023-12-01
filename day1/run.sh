#!/usr/bin/env bash

cat "$1" | sed -Ee 's/[^0-9]*([0-9]).*/\1/g' > first.txt
cat "$1" | sed -Ee 's/.*([0-9])[^0-9]*/\1/g' > second.txt
echo $(paste -d'\0' first.txt second.txt | tr '\n' '+' ) 0 | bc
