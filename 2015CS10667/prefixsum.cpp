#include <vector>
#include <omp.h>
#include <math.h>

using namespace std;

vector <int> calcPrefixSum ( vector<int> input, int num_threads) {
    omp_set_num_threads(num_threads);

    int no=input.size(),n=no;

    int log2n=0,ntemp=no;
    while (ntemp >>= 1) ++log2n;

    if((1<<log2n)!=no)
    {
        n=(1<<(log2n+1));
        log2n+=1;
    }

    for(int d=0;d<log2n;++d){
        int k=(1<<(d+1)),k2=(1<<d)-1;

        #pragma omp parallel for schedule(static) firstprivate(k,k2)
        for(int i=0;i<n;i+=k){
            if((i+k-1)<no && (i+k2)<no)
            input[i+k-1]+=input[i+k2];
        }

    }

    for(int d=log2n-2;d>-1;--d){
        int k=(1<<(d+1)),k2=(1<<d);

        #pragma omp parallel for schedule(static) firstprivate(k,k2)
        for(int i=k2;i<n;i+=k){
            if((i+k-1)<no && (i+k2-1)<no)
            input[i+k-1]+=input[i+k2-1];
        }

    }


return input;
}
