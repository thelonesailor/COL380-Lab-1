#include "iostream"
#include "vector"
#include "omp.h"
#include <stdlib.h>

using namespace std;


// stores the convex hull
vector <pair<int,int> > hull;
vector <pair<int,int> > hull2;

// stores the points
vector< pair<int, int> > points;
int n;
int threads=1,maxthreads;

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

void quickHull(pair<int,int> p1, pair<int,int> p2, int side)
{
    int index = -1,maxdistance = 0;

    // #pragma omp parallel for firstprivate(side,p1,p2)
    for (int i=0; i<n; i++)
    {
        pair<int,int> p=points[i];

        int val = (p.second - p1.second) * (p2.first - p1.first) -
                  (p2.second - p1.second) * (p.first - p1.first);

        int ps;
        if (val > 0)
            ps=1;
        else if (val < 0)
            ps=-1;
        else
            ps=0;

        if (ps == side)
        {

            int dist=(p.second - p1.second) * (p2.first - p1.first) -
                       (p2.second - p1.second) * (p.first - p1.first);
            if(dist<0)
            {dist*=-1;}

            if( dist > maxdistance)
            {
                index = i;
                maxdistance = dist;
            }

        }
    }


    if (index == -1)
    {
        #pragma omp critical
        {hull.push_back(p1);
         hull.push_back(p2);}

        return;
    }

if(threads<maxthreads)
{
    #pragma omp atomic
    --threads;

#pragma omp parallel sections
{
    #pragma omp section
    {
        #pragma omp atomic
        ++threads;
        quickHull(points[index], p1, -findSide(points[index], p1, p2));
        #pragma omp atomic
        --threads;
    }

    #pragma omp section
    {
        #pragma omp atomic
        ++threads;
        quickHull(points[index], p2, -findSide(points[index], p2, p1));
        #pragma omp atomic
        --threads;
    }
}

    #pragma omp atomic
    ++threads;
}
else
{
    quickHull(points[index], p1, -findSide(points[index], p1, p2));
    quickHull(points[index], p2, -findSide(points[index], p2, p1));
}

}


vector< pair<int, int> > calcConvexHull(vector< vector<int> > image, int num_threads) {

    hull.clear();hull2.clear();points.clear();
    threads=1;

    omp_set_nested(1);
    omp_set_num_threads(num_threads);
    maxthreads=num_threads;

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

    int minx = 2000000000, maxx = -2000000000;
    int mini=0, maxi=0;

    // #pragma omp parallel for
    for (int i=0; i<n; ++i)
    {
        int x=points[i].first;

        // #pragma omp critical
        {if (x<minx)
        {
            {minx=x;mini=i;}
        }}
        // #pragma omp critical
        {if (x>maxx)
        {
            {maxx=x;maxi=i;}
        }}
    }

if(threads<maxthreads)
{
        #pragma omp atomic
        --threads;

#pragma omp parallel sections
    {
        #pragma omp section
        {
            #pragma omp atomic
            ++threads;
            quickHull(points[mini], points[maxi], 1);
            #pragma omp atomic
            --threads;
        }

        #pragma omp section
        {
            #pragma omp atomic
            ++threads;
            quickHull(points[mini], points[maxi], -1);
            #pragma omp atomic
            --threads;
        }
    }

    #pragma omp atomic
    ++threads;
}
else
{
    quickHull(points[mini], points[maxi], 1);
    quickHull(points[mini], points[maxi], -1);
}

int s=hull.size();
for(int i=0;i<s;++i)
{
    int x=hull[i].first,y=hull[i].second,f=0,h2sz=hull2.size();

    for(int j=0;j<h2sz;++j)
    {
        if(x==hull2[j].first && y==hull2[j].second)
        {f=1;break;}
    }
    if(f==0)
    {hull2.push_back(make_pair(x,y));}
}

    return hull2;
}
