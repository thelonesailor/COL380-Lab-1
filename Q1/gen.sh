g++ -O3 -o gen gen.cpp

for power in {18,20,22}
do
n=$((2**$power))
./gen $n > ./data/prefix-$n.txt
done;

rm gen
