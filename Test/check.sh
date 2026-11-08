#!/bin/bash
# Usage: bash Test/check.sh <problem_number>
# classroom.yml 에서 문제별 채점에 사용. 0=PASS, 1=FAIL.
i=$1
next=$((i + 1))
for j in 1 2 3; do
    if [ $i -lt 3 ]; then
        a=$(awk "/=== Problem $i:/{f=1} /=== Problem $next:/{if(f) exit} f{print}" Test/output${j}.txt | tr -d '\r')
        e=$(awk "/=== Problem $i:/{f=1} /=== Problem $next:/{if(f) exit} f{print}" Test/expected${j}.txt)
    else
        a=$(awk "/=== Problem $i:/{f=1} f{print}" Test/output${j}.txt | tr -d '\r')
        e=$(awk "/=== Problem $i:/{f=1} f{print}" Test/expected${j}.txt)
    fi
    [ "$a" = "$e" ] || exit 1
done
