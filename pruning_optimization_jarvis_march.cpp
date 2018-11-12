/**
    * Team : Technomites
    * Roll Number: 2018202017 , 2018201101
    * Subject: Aps- Project Convex Hull
**/

#include <bits/stdc++.h>
#define INF 10000
using namespace std;

struct Point
{
    int x;
    int y;
};

Point p0;

int orientation(Point, Point, Point);

stack<Point> prune(Point points[], int n);

int quickHull(int, Point, Point, int, Point points[]);
int find_side(Point, Point, Point);
int line_distance(Point, Point, Point);
bool onSegment(Point, Point, Point);
bool doIntersect(Point, Point, Point, Point);
bool is_inside_polygon(Point polygon[], int, Point);

int comparator_to_sort(const void *, const void *);
Point adjacent_to_top(stack<Point> &S);
stack<Point> convexHull(Point points[], int);
int swap(Point &p1, Point &p2);
int distance_square(Point, Point);

int orientation(Point p1, Point p2, Point p3)
{
    int val = ((p2.y - p1.y) * (p3.x - p2.x)) - ((p2.x - p1.x) * (p3.y - p2.y));
    if (val == 0)
        return 0;
    if (val > 0)
        return 1;
    else
        return 2;
}

/* ############################################################################################################################# */

stack<Point> prune(Point points[], int n)
{
    stack<Point> S;
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

        if ((y < ymin) || (ymin == y && points[i].x < points[min_y].x))
            ymin = points[i].y, min_y = i;
        if ((y > ymax) || (ymax == y && points[i].x > points[max_y].x))
            ymax = points[i].y, max_y = i;

        if ((x < xmin) || (xmin == x && points[i].y < points[min_x].y))
            xmin = points[i].x, min_x = i;
        if ((x > xmax) || (xmax == x && points[i].y > points[max_x].y))
            xmax = points[i].x, max_x = i;
    }

    Point p3;
    Point p4;
    int ind1 = -1;
    int ind2 = -1;

    /*
    cout << "Xmin " << points[min_x].x << " " << points[min_x].y << "\n";
    cout << "Xmax " << points[max_x].x << " " << points[max_x].y << "\n";
    cout << "Ymin " << points[min_y].x << " " << points[min_y].y << "\n";
    cout << "Ymax " << points[max_y].x << " " << points[max_y].y << "\n";
*/

    if (points[min_x].x == points[min_y].x && points[max_x].x == points[max_y].x && points[min_x].y == points[min_y].y && points[max_x].y == points[max_y].y)
    {
        ind1 = quickHull(n, points[min_x], points[max_x], 1, points);
        ind2 = quickHull(n, points[min_x], points[max_x], -1, points);
    }
    else
    {
    }

    if (ind1 != -1)
        p3 = points[ind1];
    if (ind2 != -1)
        p4 = points[ind2];
    if (ind1 != -1)
    {
        /*         
    cout << "New Point " << p3.x << " " << p3.y << "\n";
*/
    }

    if (ind2 != -1)
    {
        /*
    cout << "New Point " << p4.x << " " << p4.y << "\n";
*/
    }

    Point polygon1[4];
    if (ind1 == -1 && ind2 == -1)
    {
        polygon1[0].x = points[min_x].x;
        polygon1[0].y = points[min_x].y;
        polygon1[1].x = points[max_x].x;
        polygon1[1].y = points[max_x].y;
        polygon1[2].x = points[min_y].x;
        polygon1[2].y = points[min_y].y;
        polygon1[3].x = points[max_y].x;
        polygon1[3].y = points[max_y].y;
    }
    else
    {
        S.push(points[min_x]);
        S.push(points[max_x]);
        if (ind1 != -1)
            S.push(p3);
        if (ind2 != -1)
            S.push(p4);
        return S;
    }

    vector<Point> v1;
    for (int i = 0; i < n; i++)
    {
        if (min_x == i || min_y == i || max_x == i || max_y == i)
        {
            v1.push_back(points[i]);
            S.push(points[i]);
        }
        else
        {
            if (is_inside_polygon(polygon1, 4, points[i]))
            {
            }
            else
            {
                v1.push_back(points[i]);
                S.push(points[i]);
            }
        }
    }

    return S;
}

/* ############################################################################################################################# */

int quickHull(int n, Point p1, Point p2, int side, Point points[])
{
    int ind = -1;
    int max_dist = 0;

    for (int i = 0; i < n; i++)
    {
        int temp = line_distance(p1, p2, points[i]);
        if (find_side(p1, p2, points[i]) == side && temp > max_dist)
        {
            ind = i;
            max_dist = temp;
        }
    }

    return ind;
}

int find_side(Point p1, Point p2, Point p)
{
    int val = (p.y - p1.y) * (p2.x - p1.x) -
              (p2.y - p1.y) * (p.x - p1.x);

    if (val > 0)
        return 1;
    if (val < 0)
        return -1;
    return 0;
}

int line_distance(Point p1, Point p2, Point p)
{
    return abs((p.y - p1.y) * (p2.x - p1.x) -
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
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    if (o1 != o2 && o3 != o4)
        return true;

    if (o1 == 0 && onSegment(p1, p2, q1))
        return true;
    if (o2 == 0 && onSegment(p1, q2, q1))
        return true;
    if (o3 == 0 && onSegment(p2, p1, q2))
        return true;
    if (o4 == 0 && onSegment(p2, q1, q2))
        return true;

    return false;
}

bool is_inside_polygon(Point polygon[], int n, Point p)
{
    if (n < 3)
        return false;
    Point extreme = {INF, p.y};
    int count = 0, i = 0;
    do
    {
        int next = (i + 1) % n;
        if (doIntersect(polygon[i], polygon[next], p, extreme))
        {
            if (orientation(polygon[i], p, polygon[next]) == 0)
                return onSegment(polygon[i], p, polygon[next]);
            count++;
        }
        i = next;
    } while (i != 0);
    return count & 1;
}

/* ############################################################################################################################# */

stack<Point> convexHull(Point points[], int n)
{
    stack<Point> chull;
    if (n < 3)
        return chull;

    int leftmost = 0;
    for (int i = 1; i < n; i++)
        if (points[i].x < points[leftmost].x)
            leftmost = i;

    int p = leftmost;
    int next;
    do
    {
        chull.push(points[p]);
        next = (p + 1) % n;
        for (int i = 0; i < n; i++)
        {
            if (orientation(points[p], points[i], points[next]) == 2)
                next = i;
        }
        p = next;

    } while (p != leftmost);

    return chull;
}

/* ############################################################################################################################# */

int main()
{

    //   Testing

    /*     int n=40000;
    int a, b;
    Point points[n];
    for (int i = 0; i < n; i++)
    {
        a=rand()%40000;
        b=rand()%40000;
        points[i].x = a;
        points[i].y = b;
    } */

    int n;
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
    }

    stack<Point> S;
    clock_t start, end;
    double time_taken;
    S = prune(points, n);
    start = clock();
    if (S.size() <= 4)
    {
    }
    else
    {
        Point pruned_points[S.size()];
        int size = S.size();
        int i;
        /*
        cout << "size " << S.size() << "\n";
*/
        for (i = 0; i < size; i++)
        {
            pruned_points[i] = S.top();
            S.pop();
        }
        S = convexHull(pruned_points, size);
    }

    cout << "Final Convex Hull Output \n";
    if (S.size() != 0)
    {
        while (!S.empty())
        {
            Point p = S.top();
            cout << "(" << p.x << ", " << p.y << ")" << endl;
            S.pop();
        }
    }
    else
        cout << "Less than three points in different orientaion.So convex hull is not possible \n";
    end = clock();
    time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    cout << "Time " << time_taken << "\n";
}
