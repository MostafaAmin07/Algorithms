// GROUP:   2 , 2
// ID:      20150257 , 20150234
// Assign:  08
// Assign:  ClosetsPair
// UVA:     10245
// Name1:   Mostafa Mohamed Amin
// Name2:   Mahmoud Ahmed Mostafa
// UVA Username: Mostafa_Amin , Dibawy

#include <cstdio>
#include <cstdlib>
#include <limits.h>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <cmath>     // please use the built-in sqrt() function
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class Type>
void Merge(Type* a, int n, bool (*IsBefore)(Type& a, Type& b))
{
    Type* temp = new Type[n];
    int rightIndex = n / 2;
    int i=0,
        j=rightIndex,
        tempI=0;
    while((i<rightIndex && j<n))
    {
        if(IsBefore(a[i],a[j]))
        {
            temp[tempI++]=a[i++];
        }
        else
        {
            temp[tempI++]=a[j++];
        }
    }
    while(i<rightIndex)
    {
        temp[tempI++]=a[i++];
    }
    while(j<n)
    {
        temp[tempI++]=a[j++];
    }
    for(int i=0;i<n;i++)
    {
        a[i]=temp[i];
    }
    delete[] temp;
}

template<class Type>
void MergeSort(Type* a, int n, bool (*IsBefore)(Type& a, Type& b))
{
    if(n > 1)
    {
        int leftSize = n / 2,
            rightSize = n - leftSize ;
        MergeSort(&a[0], leftSize, (*IsBefore));
        MergeSort(&a[leftSize], rightSize, (*IsBefore));
        Merge(a, n, (*IsBefore));
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Point
{
	double x,y;
};

bool IsBeforeX(Point& a, Point& b)
{
	return a.x<b.x;
}
bool IsBeforeY(Point& a, Point& b)
{
	return a.y<b.y;
}

double dist(Point& a, Point& b)
{
    return (double)sqrt(pow(b.x-a.x,2)+pow(b.y-a.y,2));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Sort the points p according to x before calling this function
double ClosestPair(Point* p, int n)
{
    if( n < 2)
        return INT_MAX;
    double toReturn;
    int mid = n/2;
    Point midPoint = p[mid];
    double leastDistanceLeft = ClosestPair(p, mid);
    double leastDistanceRight = ClosestPair(p+mid, n-mid);
    toReturn = leastDistanceLeft<leastDistanceRight ? leastDistanceLeft : leastDistanceRight;
    Point * midPoints = new Point[n];
    int midPointsSize = 0;
    for(int i=0;i<n;i++)
    {
        if(abs(p[i].x-midPoint.x) < toReturn)
        {
            midPoints[midPointsSize++]=p[i];
        }
    }
    MergeSort(midPoints, midPointsSize, IsBeforeY);
    for(int i=0;i<midPointsSize;i++)
    {
        for(int j=i+1;j<midPointsSize && abs(midPoints[j].y-midPoints[i].y) < toReturn;j++)
        {
            toReturn = dist(midPoints[i], midPoints[j])<toReturn ? dist(midPoints[i], midPoints[j]) : toReturn;
        }
    }
    delete [] midPoints;
    return toReturn;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
//    freopen("10245.txt","w",stdout);
	int n;
	Point *points;
	cin>>n;
	while(n) {
        points = new Point[n];
		for(int i = 0; i < n; i++) {
		    cin>>points[i].x>>points[i].y;
		}
		MergeSort(points, n, IsBeforeX);
		double distance =ClosestPair(points, n);
		if(distance < 10000)
            cout<<fixed<<setprecision(4)<<distance<<endl;
        else
            cout<<"INFINITY"<<endl;
		delete [] points;
        cin>>n;
	}
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
