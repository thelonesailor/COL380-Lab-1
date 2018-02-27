set -e

g++ -o q1 -fopenmp q1.cpp prefixsum.cpp -Wall
g++ -o gen gen.cpp -Wall
echo "compiled";
set -e

# rm -f out*
for power in {22,24,26,28}
do
n=$((2**$power))
printf "n= $n (2^$power)\n\n";
./q1 "./data/prefix-$n.txt"
mv "out.txt" "out-$n.csv"
echo "-------------------------------------"
done;

rm gen q1
