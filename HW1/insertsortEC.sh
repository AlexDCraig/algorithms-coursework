#!/bin/bash
rm insertTestEC.out
g++ insertsortEC.cpp -o insertsortEC

./insertsortEC 1000 best
./insertsortEC 2000 best
./insertsortEC 5000 best
./insertsortEC 7000 best
./insertsortEC 10000 best
./insertsortEC 11000 best
./insertsortEC 12000 best
./insertsortEC 13000 best
./insertsortEC 1000 worst
./insertsortEC 2000 worst
./insertsortEC 5000 worst
./insertsortEC 7000 worst
./insertsortEC 10000 worst
./insertsortEC 11000 worst
./insertsortEC 12000 worst
./insertsortEC 13000 worst
