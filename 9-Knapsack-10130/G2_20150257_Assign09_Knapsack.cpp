// GROUP:   2
// ID:      20150257
// Assign:  09
// Assign:  Knapsack
// UVA:     10130
// Name:    Mostafa Mohamed Amin
// UVA Username: Mostafa_Amin

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <limits.h>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Obj
{
    int v; // value (price) of object
    int w; // weight of object
};

Obj a[1000];

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T1[1001][31];
int Knapsack1(int n, int w)
{
    if(n==0)
    {
        return 0;
    }
    if(T1[n][w]!=-1)
    {
        return T1[n][w];
    }
    T1[n][w] = Knapsack1(n-1, w);
    int cw = a[n-1].w,
        cv = a[n-1].v;
    if(cw<=w)
    {
        int temp = cv+Knapsack1(n-1, w-cw);
        if(temp > T1[n][w])
        {
            T1[n][w] = temp;
        }
    }
    return T1[n][w];
}
int ComputeKnapsack1(int N, int W) // Recursive - memoization - initialize T then call Knapsack1(N,W);
{
    memset(T1,-1,sizeof(T1));
    return Knapsack1(N, W);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T2[1001][31];
int ComputeKnapsack2(int N, int W) // Bottom-up, do not save space
{
    for(int i=1; i<=N; i++)
    {
        for(int j=0; j<=W; j++)
        {
            if(i==0 || j==0)
            {
                T2[i][j]=0;
            }
            else
            {
                T2[i][j] = T2[i-1][j];
                int cw = a[i-1].w,
                    cv = a[i-1].v;
                if(cw <= j)
                {
                    int temp = cv+T2[i-1][j-cw];
                    if(temp>T2[i][j])
                    {
                        T2[i][j] = temp;
                    }
                }
            }
        }
    }
    return T2[N][W];
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T3[2][31];
int ComputeKnapsack3(int N, int W) // Bottom-up, use two rows only
{
    int cur = 0;
    for(int i=0; i<=N; i++)
    {
        for(int j=0; j<=W; j++)
        {
            if(i==0)
            {
                T3[i][j]=0;
            }
            else
            {
                T3[cur][j] = T3[1-cur][j];
                int cw = a[i-1].w,
                    cv = a[i-1].v;
                if(cw <= j)
                {
                    int temp = cv+T3[1-cur][j-cw];
                    if(temp>T3[cur][j])
                    {
                        T3[cur][j] = temp;
                    }
                }
            }
        }
        cur = 1 - cur;
    }
    return T3[N%2][W];
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T4[31];
int ComputeKnapsack4(int N, int W) // Bottom-up, save maximum space
{
    memset(T4,0,sizeof(T4));
    for(int i=0; i<N; i++)
    {
        for(int j=W; j>=0; j--)
        {
            int cw = a[i].w,
                cv = a[i].v;
            if(cw <= j)
            {
                int temp =cv+T4[j-cw];
                if(temp > T4[j])
                {
                    T4[j] = temp;
                }
            }
        }
    }
    return T4[W];
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////

int ComputeKnapsack(int N, int W) // Here we can choose the method
{
    //return ComputeKnapsack1(N,W);
    //return ComputeKnapsack2(N,W);
    //return ComputeKnapsack3(N,W);
    return ComputeKnapsack4(N,W);
}

void Compute() // Get input and call ComputeKnapsack() whenever needed
{
    int numberOfTestCases /**T**/,
        numberOfObjects/**N**/,
        numberOfPeople/**G**/,
        maxWeight/**MW**/;
    cin>>numberOfTestCases;
    while(numberOfTestCases--)
    {
        cin>>numberOfObjects;
        for(int i=0; i<numberOfObjects; i++)
        {
            cin>>a[i].v>>a[i].w;
        }
        cin>>numberOfPeople;
        int maximum=0;
        while(numberOfPeople--)
        {
            cin>>maxWeight;
            maximum+=ComputeKnapsack(numberOfObjects,maxWeight);
        }
        cout<<maximum<<endl;
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
//    freopen("10130.txt", "w", stdout);
    Compute();
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
