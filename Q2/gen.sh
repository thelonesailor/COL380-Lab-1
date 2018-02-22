g++ -o gen gen.cpp

p=4
for n in {5,10,30,50,70,100,500,1000}
do
./gen $n $n $p > ./data/feep-$n-$n.pbm
done;

rm gen
