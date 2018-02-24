#include "iostream"
#include "vector"
#include "omp.h"
#include <stdlib.h>

using namespace std;


// stores the convex hull
vector <pair<int,int> > hull;

// stores the points
vector< pair<int, int> > points;
int n;

int findSide(pair<int,int> p1, pair<int,int> p2, pair<int,int> p)
{
    int val = (p.second - p1.second) * (p2.first - p1.first) -
              (p2.second - p1.second) * (p.first - p1.first);

    if (val > 0)
        return 1;
    if (val < 0)
        return -1;
    return 0;
}

int lineDist(pair<int,int> p1, pair<int,int> p2, pair<int,int> p)
{
    return abs ((p.second - p1.second) * (p2.first - p1.first) -
               (p2.second - p1.second) * (p.first - p1.first));
}

void quickHull(pair<int,int> p1, pair<int,int> p2, int side)
{
    int ind = -1;
    int max_dist = 0;

    for (int i=0; i<n; i++)
    {
        if (findSide(p1, p2, points[i]) == side)
        {
            int temp = lineDist(p1, p2, points[i]);
            if( temp > max_dist)
            {
                ind = i;
                max_dist = temp;
            }
        }
    }


    if (ind == -1)
    {
        hull.push_back(p1);
        hull.push_back(p2);
        return;
    }

    quickHull(points[ind], p1, -findSide(points[ind], p1, p2));
    quickHull(points[ind], p2, -findSide(points[ind], p2, p1));
}


vector< pair<int, int> > calcConvexHull(vector< vector<int> > image, int num_threads) {

    int rows=image.size(),cols=image[0].size();

    for(int i=0;i<rows;++i)
    {
        for(int j=0;j<cols;++j)
        {
            if(image[i][j]==1)
            points.push_back(make_pair(i,j));
        }
    }

    n=points.size();
    if(n<3)
    {return points;}

    int minx = 1000000000, maxx = -1000000000;
    int mini=0, maxi=0;
    for (int i=0; i<n; ++i)
    {
        int x=points[i].first;

        if (x<minx)
        {minx=x;mini=i;}
        if (x>maxx)
        {maxx=x;maxi=i;}
    }

    quickHull(points[mini], points[maxi], 1);
    quickHull(points[mini], points[maxi], -1);

vector <pair<int,int> > hull2;
int s=hull.size();
for(int i=0;i<s;++i)
{
    int x=hull[i].first,y=hull[i].second,f=0;

    for(int j=0;j<hull2.size();++j)
    {
        if(x==hull2[j].first && y==hull2[j].second)
        {f=1;}
    }
    if(f==0)
    {hull2.push_back(hull[i]);}
}
    return hull2;
}
