#!/usr/bin/env bash

echo $(cat "$1" | grep -Ev '(1[3-9]|[2-9][0-9]) red' | grep -Ev '(1[4-9]|[2-9][0-9]) green' | grep -Ev '(1[5-9]|[2-9][0-9]) blue' | sed -Ee "s!Game !!g" | cut -d: -f1 | tr '\n' '+') 0 | bc
