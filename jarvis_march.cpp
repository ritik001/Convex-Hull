/**
    * Team : Technomites
    * Roll Number: 2018202017 , 2018201101
    * Subject: Aps- Project Convex Hull
**/

#include <bits/stdc++.h>
using namespace std;

struct Point
{
    int x, y;
};

/*
0 points are colinear
1 clockwise
2 anticlockwise
*/
int orientation(Point p, Point next, Point r)
{
    int val = (next.y - p.y) * (r.x - next.x) -
              (next.x - p.x) * (r.y - next.y);

    if (val == 0)
        return 0;
    return (val > 0) ? 1 : 2;
}

void convexHull(Point points[], int n)
{

    if (n < 3)
        return;

    vector<Point> chull;

    int leftmost = 0;
    for (int i = 1; i < n; i++)
        if (points[i].x < points[leftmost].x)
            leftmost = i;

    int p = leftmost;
    int next;
    do
    {
        chull.push_back(points[p]);
        next = (p + 1) % n;
        for (int i = 0; i < n; i++)
        {
            if (orientation(points[p], points[i], points[next]) == 2)
                next = i;
        }
        p = next;

    } while (p != leftmost);

    for (int i = 0; i < chull.size(); i++)
        cout << "(" << chull[i].x << ", "
             << chull[i].y << ")\n";
}

int main()
{
/*     int n;
    int a, b;
    cout << "Enter the number of points \n";
    cin >> n;
    Point points[n];
    cout << "Enter x and y co-ordinate for n Points\n";
    for (int i = 0; i < n; i++)
    {
        cin >> a;
        cin >> b;
        points[i].x = a;
        points[i].y = b;
    } */
        int n=40000;
    int a, b;
    Point points[n];
    for (int i = 0; i < n; i++)
    {
        a=rand()%40000;
        b=rand()%40000;
        points[i].x = a;
        points[i].y = b;
    }

    stack<Point> S;
    clock_t start, end;
    double time_taken;
    start = clock();
    convexHull(points, n);
    end = clock();
    time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    cout << "Time " << time_taken << "\n";
    return 0;
}
