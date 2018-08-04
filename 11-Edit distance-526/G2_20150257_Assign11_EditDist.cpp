// GROUP:   2
// ID:      20150257
// Assign:  11
// Assign:  EditDist
// UVA:     526
// Name:    Mostafa Mohamed Amin
// UVA Username: Mostafa_Amin

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define INSERT 1
#define DELETE 2
#define REPLACE 3
char a[82];
char b[82];

int D[81][81]; // D[][] is the same for all versions (no memory reduction)

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T1[81][81];
int EditDist1(int n, int m)
{
    int &to_return=T1[n][m];
    if(n == 0 && m == 0)
    {
    	to_return= 0;
    	return to_return;
    }
    else if(n == 0)
    {
    	to_return = 1 + EditDist1(n, m-1);
        D[n][m] = INSERT;
    }
    else if(m == 0)
    {
    	to_return = 1 + EditDist1(n-1, m);
        D[n][m] = DELETE;
    }
    if(to_return != -1)
    {
        return to_return;
    }
    D[n][m] = 0;
    bool not_same_char = false;
    if(a[n-1] != b[m-1])
    {
        not_same_char = true;
        D[n][m] = REPLACE;
    }
    int minimum=10000;
    int replace_value =  EditDist1(n-1, m-1)+not_same_char;
    int delete_value = EditDist1(n-1, m)+1;
    int insert_value = EditDist1(n, m-1)+1;
    if(delete_value < replace_value)
    {
        minimum=delete_value;
        D[n][m] = DELETE;
    }else minimum=replace_value;

    if(insert_value < minimum)
    {
        minimum=insert_value;
        D[n][m] = INSERT;
    }
    to_return=minimum;
    return to_return;
}
int ComputeEditDist1(int N, int M) // Recursive - memoization - initialize T then call EditDist1(N,M);
{
	memset(T1, -1, sizeof(T1));
	return EditDist1(N, M);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T2[81][81];
int ComputeEditDist2(int N, int M) // Bottom-up, do not save space
{
    T2[0][0] = 0;
    for(int i = 1 ; i < 81 ; i++)
    {
        T2[0][i] = i;
        D[0][i] = INSERT;
        T2[i][0] = i;
        D[i][0] = DELETE;
    }
    for(int i = 1 ; i < N+1 ; i++)
    {
        for(int j = 1 ; j < M+1 ; j++)
        {
            D[i][j] = 0;
            bool not_same_char = false;
            if(a[i-1] != b[j-1])
            {
                not_same_char = true;
                D[i][j] = REPLACE;
            }
            T2[i][j] = not_same_char + T2[i-1][j-1];
            int insert_value=T2[i][j-1]+1;
            int delete_value=T2[i-1][j]+1;
            if( insert_value < T2[i][j])
            {
                T2[i][j] = insert_value;
                D[i][j] = INSERT;
            }
            if( delete_value< T2[i][j])
            {
                T2[i][j] = delete_value;
                D[i][j] = DELETE;
            }
        }
    }
    return T2[N][M];
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T3[2][81];
int ComputeEditDist3(int N, int M) // Bottom-up, use two rows only
{
    int index = 0;
    T3[0][0] = 0;
    for(int i = 1 ; i < 81 ; i++)
    {
        T3[0][i] = i;
        D[0][i] = INSERT;
        D[i][0] = DELETE;
    }
    for(int i = 1 ; i < N+1 ; i++)
    {
        T3[1-index][0] = i;
        for(int j = 1 ; j < M+1 ; j++)
        {
            D[i][j] = 0;
            bool not_same_char = false;
            if(a[i-1] != b[j-1])
            {
                not_same_char = true;
                D[i][j] = REPLACE;
            }
            T3[1-index][j] = not_same_char + T3[index][j-1];
            int insert_value = T3[1-index][j-1]+1;
            int delete_value = T3[index][j]+1;
            if( insert_value< T3[1-index][j])
            {
                T3[1-index][j] = insert_value;
                D[i][j] = INSERT;
            }
            if( delete_value< T3[1-index][j])
            {
                T3[1-index][j] = delete_value;
                D[i][j] = DELETE;
            }
        }
        index = 1 - index;
    }
    return T3[index][M];
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T4[81];
int ComputeEditDist4(int N, int M) // Bottom-up, save maximum space
{
    T4[0] = 0;
    int extra = 0;
    int prev = 0;
    for(int i = 1 ; i < 81 ; i++)
    {
        T4[i] = i;
        D[0][i] = INSERT;
        D[i][0] = DELETE;
    }
    for(int i = 1 ; i < N+1 ; i++)
    {
        extra = T4[0];
        T4[0] = i;
        for(int j = 1 ; j < M+1 ; j++)
        {
            prev = T4[j];
            D[i][j] = 0;
            bool not_same_char = false;
            if(a[i-1] != b[j-1])
            {
                not_same_char = true;
                D[i][j] = REPLACE;
            }
            if(T4[j] > not_same_char+extra)
            {
                T4[j] = not_same_char + extra;
            }
            int insert_value =1 + T4[j-1];
            if(T4[j] > insert_value)
            {
                T4[j] = insert_value;
                D[i][j] = INSERT;
            }
            else if(T4[j] == prev)
            {
                D[i][j] = DELETE;
            }
            extra = prev;
        }
    }
    return T4[M];
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Oper
{
	int n,m;
	int oper;
};

Oper opers[81];

int EditDistSol(int N, int M) // Print the solution using D[][]
{
//    cout<<N<<" "<<M<<"-->"<<D[N][M]<<endl;
    if(N == 0 && M == 0)
    {
        return 0;
    }
    int index;
    if(D[N][M] == 0)
    {
        index = EditDistSol(N-1,M-1);
        opers[index].oper = 0;
    }
    else if(D[N][M] == INSERT)
    {
        index = EditDistSol(N,M-1);
        opers[index].oper = INSERT;
    }
    else if(D[N][M] == DELETE)
    {
        index = EditDistSol(N-1,M);
        opers[index].oper = DELETE;
    }
    else if(D[N][M] == REPLACE)
    {
        index = EditDistSol(N-1,M-1);
        opers[index].oper = REPLACE;
    }
    opers[index].n = N;
    opers[index].m = M-1;
    return index+1;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////

int ComputeEditDist(int N, int M) // Here we can choose the method
{
//	return ComputeEditDist1(N,M);
	return ComputeEditDist2(N,M);
//	return ComputeEditDist3(N,M);
//	return ComputeEditDist4(N,M);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

// This function does not need any modification:
void Compute() // Get input and call ComputeEditDist() whenever needed
{
	int cas=0;
	while(true)
	{
		if(!fgets(a,82,stdin))
            break; fgets(b,82,stdin);
		a[strlen(a)-1]=0;
		b[strlen(b)-1]=0;
		int N=strlen(a), M=strlen(b);
		if(cas)
            cout<<endl; // print an empty line between test cases
        cout<<a<<" "<<b<<endl;
		cout<<ComputeEditDist(N,M)<<endl;
		int index = EditDistSol(N,M);
		int step = 1;
		while(--index + 1)
        {
            int oper = opers[index].oper;
            int pos = opers[index].n;
            int change_index = opers[index].m;
            if(oper == INSERT)
            {
                cout << step << " Insert " << pos+1 << "," << b[change_index] << endl;
            }
            else if(oper == DELETE)
            {
                cout << step << " Delete " << pos << endl;
            }
            else if(oper == REPLACE)
            {
                cout << step << " Replace " << pos << "," << b[change_index] << endl;
            }
            if(oper != 0)
            {
                step++;
            }
        }
		cas++;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
#endif
//    freopen("526.txt", "r", stdin);
//	freopen("526w.txt", "w", stdout);
	Compute();
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
