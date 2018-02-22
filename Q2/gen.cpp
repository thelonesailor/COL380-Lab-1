#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]){
    int n=atoi(argv[1]),m=atoi(argv[2]);
    cout<<"P1\n# f e e p . a s c i i . pbm\n";

    int p=atoi(argv[3]);
    cout<<p<<endl;

    cout<<n<<' '<<m<<endl;
    for(int i=0;i<n;++i)
    {
        for(int j=0;j<m;++j)
        {
            int t=rand()%7;
            if(t==1)
            cout<<1<<' ';
            else
            cout<<0<<' ';

        }
        cout<<'\n';
    }
}
