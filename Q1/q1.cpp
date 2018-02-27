#include <bits/stdc++.h>
#include <omp.h>
#include <time.h>
#include <string.h>
using namespace std;

double start, endt;
double T[1000];

extern vector<int> calcPrefixSum ( vector<int> input, int num_threads) ;
vector <int> a;


int main(int argc, char *argv[]){
// omp_set_dynamic(0);     // Explicitly disable dynamic teams


char* filename=argv[1];

int n;
fstream myfile;
myfile.open(filename);
myfile>>n;
cout<<n<<endl;
a.resize(n);

int *prefix;
prefix=(int*) calloc((n+2),sizeof(int));


for(int i=0;i<n;++i)
{
    myfile>>a[i];
}
myfile.close();


int times=50;

prefix[0]=a[0];
for(int i=1;i<n;++i)
{prefix[i]=prefix[i-1]+a[i];}

int maxp=64;

//1,2...64 threads
for(int p=1;p<=maxp;p*=2)
{
for(int m=0;m<times;++m)
{

start=omp_get_wtime();

vector <int> pre;
pre=calcPrefixSum(a,p);

endt=omp_get_wtime();
T[p] += (endt - start);

for(int i=0;i<n;++i)
{assert (pre[i]==prefix[i]);}

}
T[p]/=times;
printf("T[%d]=%f seconds\n",p,T[p]);

}


myfile.open("out.txt",fstream::out);
for(int p=1;p<=maxp;p*=2)
{
    double S=(T[1]/T[p]);
    double E=S/p;
    myfile<<p<<','<<T[p]<<','<<S<<','<<E<<'\n';
    cout<<p<<','<<T[p]<<','<<S<<','<<E<<'\n';
}
myfile.close();


    return 0;
}
