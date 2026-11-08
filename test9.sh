#!/bin/bash
# Homework 9 — 문제별 채점 (3개 테스트 케이스 기준)

g++ main.cpp problem1.cpp problem2.cpp problem3.cpp \
    -o hw9_main -std=c++17 -fsanitize=address -g
if [ $? -ne 0 ]; then
    echo "Compile Error"
    exit 1
fi

for j in 1 2 3; do
    ./hw9_main Test/case${j}.txt > Test/output${j}.txt 2>/dev/null
    if [ $? -ne 0 ]; then
        echo "Runtime Error (case${j})"
        rm -f hw9_main
        exit 1
    fi
done
rm -f hw9_main

extract() {
    local file=$1 i=$2 next=$((i + 1))
    if [ $i -lt 3 ]; then
        awk "/=== Problem $i:/{f=1} /=== Problem $next:/{if(f) exit} f{print}" "$file" | tr -d '\r'
    else
        awk "/=== Problem $i:/{f=1} f{print}" "$file" | tr -d '\r'
    fi
}

check() {
    local i=$1
    for j in 1 2 3; do
        [ "$(extract Test/output${j}.txt $i)" = "$(extract Test/expected${j}.txt $i)" ] || return 1
    done
}

for i in 1 2 3; do
    if check $i; then
        echo "Problem $i: PASS"
    else
        echo "Problem $i: FAIL"
    fi
done
