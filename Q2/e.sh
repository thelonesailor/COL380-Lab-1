#!/bin/bash
set -e

# g++ -o q2p -fopenmp p2_2015cs10667.cpp tester.cpp
g++ -o q2s -fopenmp p2_2015cs10667_s.cpp tester.cpp

for n in {5,10,30,50,70,100,500,1000}
do
echo "$n * $n";
in="./data/feep-$n-$n.pbm"
./q2s < $in
echo "-----------------------------";
done;

./q2s < feep_input.pbm

rm q2s
