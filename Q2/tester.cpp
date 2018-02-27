#include "iostream"
#include "vector"
#include "ctime"
#include "omp.h"
#include <bits/stdc++.h>

using namespace std;

extern vector< pair<int, int> > calcConvexHull(vector< vector<int> > image, int num_threads);
extern vector< pair<int, int> > calcConvexHull_s(vector< vector<int> > image);

double T[1000];

int main() {
    string file_headers;
    getline(cin, file_headers);
    getline(cin, file_headers);


    int m, n;
    cin >> m >> n;
    vector< vector<int> > image;
    image.resize(m);

    int count=0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            int a;
            cin >> a;
            image[i].push_back(a);
        }
    }

    vector< pair<int, int> > convexHull_s = calcConvexHull_s(image);
    vector< vector<int> > image_s;
    image_s.resize(m);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            image_s[i].push_back(0);
        }
    }
    for (int i = 0; i < convexHull_s.size(); i++){
        int x=convexHull_s[i].first,y=convexHull_s[i].second;
        image_s[x][y]=1;
    }


    int times=30,maxp=64;
    vector< pair<int, int> > convexHull_p;
    for(int p=1;p<=maxp;p*=2)
    {

        T[p]=0;
        for(int u=0;u<times;++u){

        double start_time = omp_get_wtime();
        convexHull_p = calcConvexHull(image,p);
        double time_taken = omp_get_wtime() - start_time;
        T[p]+=time_taken;

        }
        T[p]/=times;

        // printf("convexHull_s.size()=%d\n",convexHull_s.size());
        // for(int k=0;k<convexHull_s.size();++k)
        // {printf("(%d,%d)",convexHull_s[k].second,convexHull_s[k].second);}
        // printf("\n");
        // printf("convexHull_p.size()=%d\n",convexHull_p.size());
        // for(int k=0;k<convexHull_p.size();++k)
        // {printf("(%d,%d)",convexHull_p[k].second,convexHull_p[k].second);}
        // printf("\n");

        vector< vector<int> > image_p;
        image_p.resize(m);
        for (int i = 0; i < m; i++) {
                image_p[i].clear();
            for (int j = 0; j < n; j++) {
                image_p[i].push_back(0);
            }
        }
        for (int i = 0; i < convexHull_p.size(); i++){
            int x=convexHull_p[i].first,y=convexHull_p[i].second;
            if(image_p[x][y]==1)
            {cout<<"Repeated point\n";}
            image_p[x][y]=1;
        }
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if(image_s[i][j]!=image_p[i][j])
                {cout<<"Error - wrong\n";
                    cout<<i<<" "<<j<<'\n';
                    cout<<image_s[i][j]<<" "<<image_p[i][j]<<'\n';

                    for(int k=0;k<convexHull_s.size();++k)
                    {printf("(%d,%d)",convexHull_s[k].second,convexHull_s[k].second);}
                    printf("\n");
                    for(int k=0;k<convexHull_p.size();++k)
                    {printf("(%d,%d)",convexHull_p[k].second,convexHull_p[k].second);}
                    printf("\n");

                goto l;}
            }
        }


        printf("T[%d]=%f seconds\t",p,T[p]);
        cout<<"Correct\n";
        l:;
    }

fstream myfile;
    myfile.open("outq2.txt",fstream::out);
    for(int p=1;p<=maxp;p*=2)
    {
        double S=(T[1]/T[p]);
        double E=S/p;
        myfile<<p<<','<<T[p]<<','<<S<<','<<E<<'\n';
        cout<<p<<','<<T[p]<<','<<S<<','<<E<<'\n';
    }
    myfile.close();


    // cout<< convexHull.size() << endl;
    // for (int i = 0; i < convexHull.size(); i++){
    //     cout << convexHull[i].first << " " << convexHull[i].second << endl;
    // }

    return 0;
}
