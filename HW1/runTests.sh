#!/bin/bash
# Compile and run tests on insert and merge sort files.

g++ insertsortTest.cpp -o insertsortTest

for i in 1 2 3
do
	./insertsortTest 11000
done

for i in 1 2 3
do
	./insertsortTest 12000
done

for i in 1 2 3
do
	./insertsortTest 13000
done

g++ mergesortTest.cpp -o mergesortTest

for i in 1 2 3 
do
	./mergesortTest 11000
done

for i in 1 2 3
do
	./mergesortTest 12000
done

for i in 1 2 3
do
	./mergesortTest 13000
done
