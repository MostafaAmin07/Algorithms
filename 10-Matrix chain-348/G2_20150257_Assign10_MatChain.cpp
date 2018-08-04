// GROUP:   2
// ID:      20150257
// Assign:  10
// Assign:  MatChain
// UVA:     348
// Name:    Mostafa Mohamed Amin
// UVA Username: Mostafa_Amin

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int p[11]; // the dimensions of matrices

int T[11][11]; // T[a][b]=the optimal number of multiplication of p[a]...p[b]
int D[11][11]; // D[a][b]=the decision (value of k) that gets T[a][b]

// Top down version
int MatChain(int a, int b) // Recursive, cost of multiplying the b-a matrices with indexes: a...b-1
{
    if(a+1 == b)
    {
        T[a][b]=0;
        return 0;
    }
    if(T[a][b] >= 0)
    {
        return T[a][b];
    }
    T[a][b] = INT_MAX;
    for(int k = a+1; k < b; k++)
    {
        int v = MatChain(a, k) + MatChain(k, b) + p[a] * p[k] * p[b];
        if(v < T[a][b])
        {
            T[a][b] = v;
            D[a][b] = k;
        }
    }
    return T[a][b];
}

void MatChainTopDown(int n) // Initialize T then call MatChain(0,n)
{
    memset(T, -1, sizeof(T));
    MatChain(0, n);
}

// BottomUp version
void MatChainBottomUp(int n)
{
    memset(T, -1, sizeof(T));
    memset(D, 0, sizeof(D));
    int j=0;
    for(int s = 1; s <= n; s++)
    {
        for(int i = 0; i+s <= n; i++)
        {
            j = i + s;
            MatChain(i,j);
        }
    }
}

// Recursive to output the solution for both versions
void MatChainSol(int a, int b)
{
    if(a+1 == b)
    {
        cout << "A" << a+1;
        return;
    }
    int k = D[a][b];
    cout << "(";
    MatChainSol(a, k);
    cout << " x ";
    MatChainSol(k, b);
    cout << ")";

}

void Compute()
{
    int testCaseNumber = 1;
    int numberOfArrays;
    cin>>numberOfArrays;
    while(numberOfArrays)
    {
        for(int i=0; i<numberOfArrays; ++i)
        {
            cin >> p[i] >> p[i+1];
        }
        if(testCaseNumber%2)
            MatChainBottomUp(numberOfArrays);
        else
            MatChainTopDown(numberOfArrays);
        cout << "Case " << testCaseNumber++ << ": ";
        MatChainSol(0, numberOfArrays);
        cout << "\n";
        cin>>numberOfArrays;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    //freopen("input_assign10_00348.txt", "r", stdin);
    Compute();
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
