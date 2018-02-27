g++ -O3 -o gen gen.cpp

for power in {22,23,24,25,26,27,28}
do
n=$((2**$power))
./gen $n > ./data/prefix-$n.txt
done;

rm gen
