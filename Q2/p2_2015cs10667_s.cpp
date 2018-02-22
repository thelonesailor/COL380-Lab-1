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

// returns the square of distance between p1 and p2
// int dist(pair<int,int> p, pair<int,int> q)
// {
//     int xdiff=(p.first - q.first),ydiff=(p.second - q.second);
//     return (ydiff*ydiff + xdiff*xdiff);
// }

// // returns a value proportional to the distance
// // between the point p and the line joining the
// // points p1 and p2
int lineDist(pair<int,int> p1, pair<int,int> p2, pair<int,int> p)
{
    return abs ((p.second - p1.second) * (p2.first - p1.first) -
               (p2.second - p1.second) * (p.first - p1.first));
}
//
// // End points of line L are p1 and p2.  side can have value
// // 1 or -1 specifying each of the parts made by the line L
void quickHull(pair<int,int> p1, pair<int,int> p2, int side)
{
    int ind = -1;
    int max_dist = 0;

    // finding the point with maximum distance
    // from L and also on the specified side of L.
    for (int i=0; i<n; i++)
    {
        int temp = lineDist(p1, p2, points[i]);
        if (findSide(p1, p2, points[i]) == side && temp > max_dist)
        {
            ind = i;
            max_dist = temp;
        }
    }

    // If no point is found, add the end points
    // of L to the convex hull.
    if (ind == -1)
    {
        hull.push_back(p1);
        hull.push_back(p2);
        return;
    }

    // Recur for the two parts divided by a[ind]
    quickHull(points[ind], p1, -findSide(points[ind], p1, p2));
    quickHull(points[ind], p2, -findSide(points[ind], p2, p1));
}

//
// void printHull(pair<int,int> a[], int n)
// {
//     // a[i].second -> y-coordinate of the ith point
//     if (n < 3)
//     {
//         cout << "Convex hull not possible\n";
//         return;
//     }
//
//     // Finding the point with minimum and
//     // maximum x-coordinate
//     int min_x = 0, max_x = 0;
//     for (int i=1; i<n; i++)
//     {
//         if (a[i].first < a[min_x].first)
//             min_x = i;
//         if (a[i].first > a[max_x].first)
//             max_x = i;
//     }
//
//     // Recursively find convex hull points on
//     // one side of line joining a[min_x] and
//     // a[max_x]
//     quickHull(a, n, a[min_x], a[max_x], 1);
//
//     // Recursively find convex hull points on
//     // other side of line joining a[min_x] and
//     // a[max_x]
//     quickHull(a, n, a[min_x], a[max_x], -1);
//
//     cout << "The points in Convex Hull are:\n";
//     while (!hull.empty())
//     {
//         cout << "(" <<( *hull.begin()).first << ", "
//              << (*hull.begin()).second << ") ";
//         hull.erase(hull.begin());
//     }
// }

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
