#include "iostream"
#include "vector"
#include "omp.h"
#include <stdlib.h>

using namespace std;


// stores the convex hull
vector <pair<int,int> > hull_s;
vector <pair<int,int> > hull2_s;

// stores the points
vector< pair<int, int> > points_s;
int n_s;

int findSide_s(pair<int,int> p1, pair<int,int> p2, pair<int,int> p)
{
    int val = (p.second - p1.second) * (p2.first - p1.first) -
              (p2.second - p1.second) * (p.first - p1.first);

    if (val > 0)
        return 1;
    if (val < 0)
        return -1;
    return 0;
}

int lineDist_s(pair<int,int> p1, pair<int,int> p2, pair<int,int> p)
{
    return abs ((p.second - p1.second) * (p2.first - p1.first) -
               (p2.second - p1.second) * (p.first - p1.first));
}

void quickHull_s(pair<int,int> p1, pair<int,int> p2, int side)
{
    int ind = -1;
    int max_dist = 0;

    for (int i=0; i<n_s; i++)
    {
        if (findSide_s(p1, p2, points_s[i]) == side)
        {
            int temp = lineDist_s(p1, p2, points_s[i]);
            if( temp > max_dist)
            {
                ind = i;
                max_dist = temp;
            }
        }
    }


    if (ind == -1)
    {
        hull_s.push_back(p1);
        hull_s.push_back(p2);
        return;
    }

    quickHull_s(points_s[ind], p1, -findSide_s(points_s[ind], p1, p2));
    quickHull_s(points_s[ind], p2, -findSide_s(points_s[ind], p2, p1));

}


vector< pair<int, int> > calcConvexHull_s(vector< vector<int> > image) {
    // cout<<"_s called"<<endl;

    int rows=image.size(),cols=image[0].size();

    for(int i=0;i<rows;++i)
    {
        for(int j=0;j<cols;++j)
        {
            if(image[i][j]==1)
            points_s.push_back(make_pair(i,j));
        }
    }

    n_s=points_s.size();
// cout<<n_s<<endl;
    if(n_s<3)
    {return points_s;}

    int minx = 1000000000, maxx = -1000000000;
    int mini=0, maxi=0;

    for (int i=0; i<n_s; ++i)
    {
        int x=points_s[i].first;

        if (x<minx)
        {
            {minx=x;mini=i;}
        }
        if (x>maxx)
        {
            {maxx=x;maxi=i;}
        }
    }

    quickHull_s(points_s[mini], points_s[maxi], 1);
    quickHull_s(points_s[mini], points_s[maxi], -1);

hull2_s.clear();
int s=hull_s.size();
for(int i=0;i<s;++i)
{
    int x=hull_s[i].first,y=hull_s[i].second,f=0;

    for(int j=0;j<hull2_s.size();++j)
    {
        if(x==hull2_s[j].first && y==hull2_s[j].second)
        {f=1;break;}
    }
    if(f==0)
    {hull2_s.push_back(make_pair(x,y));}
}

    return hull2_s;
}
