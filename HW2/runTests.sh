#!/bin/bash
# Compile and run tests on stooge sort files.

g++ stoogeTest.cpp -o stoogeTest

rm stoogeTest.out

./stoogeTest 100
./stoogeTest 200
./stoogeTest 300
./stoogeTest 400
./stoogeTest 500
./stoogeTest 600
./stoogeTest 700
