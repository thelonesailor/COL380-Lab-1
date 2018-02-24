g++ -O3 -o gen gen.cpp

for n in {5,10,30,50,70,100,500,1000}
do
m=$n
for p in {1,2,4,8,16,32}
do
./gen $n $m $p > ./data/feep-$n-$m-$p.pbm
done;
done;

rm gen
