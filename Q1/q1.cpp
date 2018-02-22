#include <bits/stdc++.h>
#include <omp.h>
#include <time.h>
using namespace std;

double start, end;
double Ts=0,Tp=0,S,E;


int main(int argc, char *argv[]){



int num_threads=atoi(argv[1]);
omp_set_dynamic(0);     // Explicitly disable dynamic teams
omp_set_num_threads(num_threads);

char* filename=argv[2];

fstream myfile;
myfile.open(filename);
int n,no;
myfile>>n;
no=n;//original n

int log2n=log2(n);
if(pow(2,log2n)!=n)
{
    n=pow(2,log2n+1);
    log2n+=1;
}

int *a,*original,*prefix;
a=(int*) calloc((n+2),sizeof(int));
original=(int*) calloc((n+2),sizeof(int));
prefix=(int*) calloc((n+2),sizeof(int));


for(int i=0;i<no;++i)
{
    myfile>>a[i];
    original[i]=a[i];
}
for(int i=no;i<n;++i)
{
    original[i]=0;
    a[i]=0;
}

myfile.close();

int last=a[n-1];
int times=200;


//serial program
for(int m=0;m<times;++m)
{
start=omp_get_wtime();
{
    prefix[0]=a[0];
    for(int i=1;i<n;i++)
    {prefix[i]=prefix[i-1]+a[i];}
}
end=omp_get_wtime();
Ts += (end - start);
}
Ts/=times;
printf("Ts=%f seconds\n",Ts);


// parallel program
for(int m=0;m<times;++m)
{
    for(int i=0;i<n;++i)
    {a[i]=original[i];}

start=omp_get_wtime();
{
    for(int d=0;d<log2n;++d){
        unsigned int k=(1<<(d+1)),k2=(1<<d);

        #pragma omp parallel for schedule(static) firstprivate(k,k2)
        for(int i=0;i<n;i+=k){
            a[i+k-1]+=a[i+k2-1];
        }

    }

    a[n-1]=0;
    for(int d=log2n-1;d>-1;--d){
        unsigned int k=(1<<(d+1)),k2=(1<<d);

        #pragma omp parallel for schedule(static) firstprivate(k,k2)
        for(int i=0;i<n;i+=k){
            int t=a[i+k2-1];
            a[i+k2-1]=a[i+k-1];
            a[i+k-1]+=t;
        }

    }
    a[n]=a[n-1]+last;
}
end=omp_get_wtime();
Tp += (end - start);

for(int i=1;i<=n;++i)
{assert (a[i]==prefix[i-1]);}

}
Tp/=times;
printf("Tp=%f seconds\n",Tp);//wall clock time


S=Ts/Tp;
printf("Speedup=%f\n",S);
E=S/num_threads;
printf("Efficiency=%f\n",E);
// printf("Overhead=%f\n",(num_threads*Tp-Ts)/num_threads);

// for(int i=1;i<no+1;++i)
// {printf("%d ",a[i]);}
// printf("\n");

    return 0;
}
