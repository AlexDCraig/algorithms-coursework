#!/bin/bash

g++ mergesortTest.cpp -o mergesortTest

rm mergesortTest.out

./mergesortTest 1000
./mergesortTest 2000
./mergesortTest 3000
./mergesortTest 4000
./mergesortTest 5000
./mergesortTest 6000
./mergesortTest 7000
