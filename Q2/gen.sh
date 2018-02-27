g++ -O3 -o gen gen.cpp

for n in {1000,2000,3000,4000,5000,6000}
do
m=$n
./gen $n $m > ./data/feep-$n-$m.pbm
done;

rm gen
