#!/bin/bash
set -e
g++ -o ch -fopenmp convexhull.cpp tester.cpp convexhull_s.cpp

# ./gen.sh

# rm -f out*
for n in {2000,3000,4000,5000}
do
m=$n
echo "$n * $m";
in="./data/feep-$n-$m.pbm"
./ch < $in
mv "outq2.txt" "out-$n-$m.csv"
echo "-----------------------------------";
done;

rm ch
