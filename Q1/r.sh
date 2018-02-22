g++ -o q1 -fopenmp q1.cpp
g++ -o gen gen.cpp

file="input.txt"

for power in {13,17}
do
n=$((2**$power))
printf "n= $n (2^$power)\n\n";
for p in {2,4,8,16}
do
echo "p= $p";
rm -f $file
touch $file
./gen $n >> $file
./q1 $p $file 
printf "\n";
done;
echo "-------------------------------------"
done;
