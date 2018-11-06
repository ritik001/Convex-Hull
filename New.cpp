/**
    * Team : Technomites
    * Roll Number: 2018202017 , 2018201101
    * Subject: Aps- Project Convex Hull
**/

#include <bits/stdc++.h>
using namespace std;

struct Point{
    int x;
    int y;
};

#define INF 10000
int lineDist(Point,Point,Point);
int findSide(Point,Point,Point);
int quickHull(int,Point,Point,int);
bool isInside(Point polygon[],int,Point);


Point points[] = {{0, 2}, {2, 0}, {2, 4}, {4, 2},{1,2},{2,2},{3,3}};

int  n;

Point p0;

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

void convexHull(Point points[], int n) 
{ 
   int ymin = points[0].y;
   int ymax = points[0].y;
   int xmin = points[0].x;
   int xmax = points[0].x;

   int min_x = 0;
   int max_x = 0;
   int min_y = 0;
   int max_y = 0;

   for (int i = 1; i < n; i++) 
   {

     int x = points[i].x; 
     int y = points[i].y; 

     if ((y < ymin) || (ymin == y && points[i].x < points[min_x].x)) 
        ymin = points[i].y, min_y = i; 
     if ((y > ymax) || (ymax == y && points[i].x > points[max_x].x)) 
        ymax = points[i].y, max_y = i; 

     if ((x < xmin) || (xmin == x && points[i].y < points[min_y].y)) 
        xmin = points[i].x, min_x = i; 
/*     if(i==3)
    {
        cout << "hi ";
        cout << points[i].x << "\n";
        cout << "dgdhd " << xmax << "\n";
    } */
     if ((x > xmax) || (xmax == x && points[i].y > points[max_y].y)) 
        xmax = points[i].x, max_x = i; 

   }
    Point p3;
    Point p4;
    int ind1=-1;
    int ind2=-1;

/*     cout << "Xmin " << points[min_x].x << " " << points[min_x].y << "\n";
    cout << "Xmax " << points[max_x].x << " " << points[max_x].y << "\n";
    cout << "Ymin " << points[min_y].x << " " << points[min_y].y << "\n";
    cout << "Ymax " << points[max_y].x << " " << points[max_y].y << "\n"; */

    if(points[min_x].x == points[min_y].x && points[max_x].x == points[max_y].x && points[min_x].y == points[min_y].y && points[max_x].y == points[max_y].y )
    {   
        ind1=quickHull(n,points[min_x],points[max_x],1);
        ind2=quickHull(n,points[min_x],points[max_x],-1);
    }
    else
        {}

    if(ind1!=-1)
        p3=points[ind1];
    if(ind2!=-1)
        p4=points[ind2];
    if(ind1!=-1)
    {
        cout << "New Point " << p3.x << " " << p3.y << "\n";
    }

    if(ind2!=-1)
    {
        cout << "New Point " << p4.x << " " << p4.y << "\n";
    }

    Point polygon1[4];
    if(ind1==-1 && ind2==-1)
    {
    cout << "hei" << "\n";
    polygon1[0].x=points[min_x].x;
    polygon1[0].y=points[min_x].y;
    polygon1[1].x=points[max_x].x;
    polygon1[1].y=points[max_x].y;
    polygon1[2].x=points[min_y].x;
    polygon1[2].y=points[min_y].y;
    polygon1[3].x=points[max_y].x;
    polygon1[3].y=points[max_y].y;
    }
    cout << "Xmin " << polygon1[0].x << " " << polygon1[0].y << "\n";
    cout << "Xmax " << polygon1[1].x << " " << polygon1[1].y << "\n";
    cout << "Ymin " << polygon1[2].x << " " << polygon1[2].y << "\n";
    cout << "Ymin " << polygon1[3].x << " " << polygon1[3].y << "\n";

/*     int j=0;
    for(int i=0;i<n;i++)
    {
        if(min_x == i || min_y == i || max_x == i || max_y == i)
            {
                polygon1[j].x=points[i].x;
                polygon1[j].y=points[i].y;
                j++;
            }
    }
    } */

    vector<Point> v1;
    for(int i=0;i<n;i++)
    {
        if(min_x == i || min_y == i || max_x == i || max_y == i)
        {
            v1.push_back(points[i]);
            cout << "here "<< "\n";
        }
        else
        {
        if(isInside(polygon1,4,points[i]))
        {
        }
        else
        {
/*             cout << points[i].x << " " << points[i].y << "\n"; */
            v1.push_back(points[i]);
        }
        }
    }

    cout << "Size " << v1.size() << "\n";




} 

int quickHull(int n,Point p1,Point p2, int side) 
{ 
    int ind = -1; 
    int max_dist = 0; 

    for (int i=0; i<n; i++) 
    { 
        int temp = lineDist(p1, p2, points[i]); 
        if (findSide(p1, p2, points[i]) == side && temp > max_dist) 
        { 
            ind = i; 
            max_dist = temp; 
        } 
    } 

    return ind;

}

int findSide(Point p1, Point p2, Point p) 
{ 
    int val = (p.y - p1.y) * (p2.x - p1.x) - 
              (p2.y - p1.y) * (p.x - p1.x); 
  
    if (val > 0) 
        return 1; 
    if (val < 0) 
        return -1; 
    return 0; 
} 
  
// returns a value proportional to the distance 
// between the point p and the line joining the 
// points p1 and p2 
int lineDist(Point p1, Point p2, Point p) 
{ 
    return abs ((p.y - p1.y) * (p2.x - p1.x) - 
               (p2.y - p1.y) * (p.x - p1.x)); 
} 

bool onSegment(Point p, Point q, Point r) 
{ 
    if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) && 
            q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y)) 
        return true; 
    return false; 
} 

bool doIntersect(Point p1, Point q1, Point p2, Point q2) 
{ 
    // Find the four orientations needed for general and 
    // special cases 
    int o1 = orientation(p1, q1, p2); 
    int o2 = orientation(p1, q1, q2); 
    int o3 = orientation(p2, q2, p1); 
    int o4 = orientation(p2, q2, q1); 
  
    // General case 
    if (o1 != o2 && o3 != o4) 
        return true; 
  
    // Special Cases 
    // p1, q1 and p2 are colinear and p2 lies on segment p1q1 
    if (o1 == 0 && onSegment(p1, p2, q1)) return true; 
  
    // p1, q1 and p2 are colinear and q2 lies on segment p1q1 
    if (o2 == 0 && onSegment(p1, q2, q1)) return true; 
  
    // p2, q2 and p1 are colinear and p1 lies on segment p2q2 
    if (o3 == 0 && onSegment(p2, p1, q2)) return true; 
  
     // p2, q2 and q1 are colinear and q1 lies on segment p2q2 
    if (o4 == 0 && onSegment(p2, q1, q2)) return true; 
  
    return false; // Doesn't fall in any of the above cases 
} 

bool isInside(Point polygon[], int n, Point p) 
{ 
    // There must be at least 3 vertices in polygon[] 
    if (n < 3)  return false; 
  
    // Create a point for line segment from p to infinite 
    Point extreme = {INF, p.y}; 
  
    // Count intersections of the above line with sides of polygon 
    int count = 0, i = 0; 
    do
    { 
        int next = (i+1)%n; 
  
        // Check if the line segment from 'p' to 'extreme' intersects 
        // with the line segment from 'polygon[i]' to 'polygon[next]' 
        if (doIntersect(polygon[i], polygon[next], p, extreme)) 
        { 
            // If the point 'p' is colinear with line segment 'i-next', 
            // then check if it lies on segment. If it lies, return true, 
            // otherwise false 
            if (orientation(polygon[i], p, polygon[next]) == 0) 
               return onSegment(polygon[i], p, polygon[next]); 
  
            count++; 
        } 
        i = next; 
    } while (i != 0); 
  
    // Return true if count is odd, false otherwise 
    return count&1;  // Same as (count%2 == 1) 
} 






int main()
{

    n=7;
/*     int a,b;
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
    } */
    convexHull(points,n);

}