#!/bin/bash
set -e

g++ -o ch -fopenmp convexhull.cpp tester.cpp

for n in {5,10,30,50,70,100,500,1000}
do
m=$n
for
echo "$n * $m";
in="./data/feep-$n-$m-$p.pbm"
./ch < $in
echo "-----------------------------";
done;

rm ch
