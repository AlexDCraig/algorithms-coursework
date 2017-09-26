#!/bin/bash
#!/bin/bash
rm mergeTestEC.out
g++ mergesortEC.cpp -o mergesortEC

./mergesortEC 1000 best
./mergesortEC 2000 best
./mergesortEC 5000 best
./mergesortEC 7000 best
./mergesortEC 10000 best
./mergesortEC 11000 best
./mergesortEC 12000 best
./mergesortEC 13000 best
./mergesortEC 1000 worst
./mergesortEC 2000 worst
./mergesortEC 5000 worst
./mergesortEC 7000 worst
./mergesortEC 10000 worst
./mergesortEC 11000 worst
./mergesortEC 12000 worst
./mergesortEC 13000 worst
