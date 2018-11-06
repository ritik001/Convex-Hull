/**
    * Team : Technomites
    * Roll Number: 2018202017 , 2018201101
    * Subject: Aps- Project Convex Hull
**/

#include <bits/stdc++.h>
#include <time.h>
using namespace std;

struct Point{
    int x;
    int y;
};

Point p0;

int swap(Point &p1,Point &p2)
{
    Point temp=p1;
    p1=p2;
    p2=temp;
}

int distance_square(Point p1,Point p2)
{
    return pow(p1.x-p2.x,2)+pow(p1.y-p2.y,2);
}

/*
0 points are colinear
1 clockwise
2 anticlockwise
*/

int orientation(Point p1,Point p2,Point p3)
{
    int val=((p2.y-p1.y)*(p3.x-p2.x))-((p2.x-p1.x)*(p3.y-p2.y));
    if(val == 0)
        return 0;
    if(val > 0)
        return 1;
    else
        return 2;
}

int comparator_to_sort(const void *vp1,const void *vp2)
{
    Point *p1=(Point*)vp1;
    Point *p2=(Point*)vp2;
    int o=orientation(p0,*p1,*p2);
    if(o == 0)
    {
        if(distance_square(p0,*p2) >= distance_square(p0,*p1))
            return -1;
        else
            return 1;
    }
    else if(o == 1)
        return 1;
    else
        return 0;    
}

Point adjacent_to_top(stack<Point> &S) 
{ 
    Point p = S.top(); 
    S.pop(); 
    Point res = S.top(); 
    S.push(p); 
    return res; 
} 

stack<Point> convexHull(Point points[], int n) 
{ 
   int ymin = points[0].y;
   int min = 0; 
   for (int i = 1; i < n; i++) 
   { 
     int y = points[i].y; 
  
     if ((y < ymin) || (ymin == y && points[i].x < points[min].x)) 
        ymin = points[i].y, min = i; 
   } 
  
   swap(points[0], points[min]); 
   p0 = points[0]; 
   qsort(&points[1], n-1, sizeof(Point), comparator_to_sort); 
  
   int m=1;
   for (int i=1; i<n; i++) 
   { 
       while (i < n-1 && orientation(p0, points[i], points[i+1]) == 0) 
          i++; 
       points[m] = points[i]; 
       m++;
   } 
   stack<Point> S; 
   if (m < 3) 
    return S; 
   S.push(points[0]); 
   S.push(points[1]); 
   S.push(points[2]); 
  
   for (int i = 3; i < m; i++) 
   { 
      while (orientation(adjacent_to_top(S), S.top(), points[i]) != 2) 
         S.pop(); 
      S.push(points[i]); 
   } 
    return S;
} 


int main()
{

    clock_t start, end;
    double time_taken;
    int n;
    int a,b;
    cout << "Enter the number of points \n";
    cin >> n;
    Point points[n];
    cout << "Enter x and y co-ordinate for n Points\n";
    for(int i=0;i<n;i++)
    {
        cin >> a;
        cin >> b;
        points[i].x=a;
        points[i].y=b;
    }
    start = clock();
    stack<Point> S=convexHull(points,n);
    cout << "\n";
    if(S.size()!=0)
    {
        while (!S.empty()) 
        { 
        Point p = S.top(); 
        cout << "(" << p.x << ", " << p.y <<")" << endl; 
        S.pop(); 
        } 
    }
    else
        cout << "Less than three points in different orientaion.So convex hull is not possible \n";
    end = clock();
    time_taken = ((double) (end - start)) / CLOCKS_PER_SEC;
    cout << "Time " << time_taken << "\n";

}