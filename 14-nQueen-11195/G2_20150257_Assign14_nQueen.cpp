// GROUP:   2
// ID:      20150257
// Assign:  14
// Assign:  nQueen problem
// UVA:     11195
// Name:    Mostafa Mohamed Amin
// UVA Username: Mostafa_Amin

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;


#define MAX_N 15
int n;
int sol_cnt;
bool cols[MAX_N];
bool top_left[MAX_N*2-1];
bool top_right[MAX_N*2-1];
bool bad_pos[MAX_N][MAX_N];
//bool board[MAX_N][MAX_N];

//void print()
//{
//    for(int i=0;i<n;i++){
//        for(int j=0;j<n;j++){
//            if(board[i][j]&&bad_pos[i][j]){
//                cout<<"* ";
//            }
//            else{
//                cout<<board[i][j]<<" ";
//            }
//        }
//        cout<<endl;
//    }
//}

void initialize_arrays()
{
    int i;
    for(i=0;i<MAX_N;i++)
        cols[i]=false;
    for(i=0;i<MAX_N*2-1;i++)
        top_left[i] = top_right[i] = false;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool valid(int i, int j)
{
    return !(cols[j] || top_left[i-j+n] || top_right[i+j] || bad_pos[i][j]);
}

void change_valid(int i, int j)
{
    cols[j] = ! cols[j];
    top_left[i-j+n] = ! top_left[i-j+n];
    top_right[i+j] = ! top_right[i+j];
//    board[i][j] = ! board[i][j];
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Dancing Links:

int F[MAX_N]; // head=F[0], elements are indexed from 1 to n, F[n]=0
int B[MAX_N]; // B[0]=n, B[1]=0
void Remove(int i) {F[B[i]]=F[i]; B[F[i]]=B[i];}
void Restore(int i) {B[F[i]]=i; F[B[i]]=i;}
void InitDancingLinks(int n)
{
	int i;
	for(i=0;i<n;i++) F[i]=i+1; F[n]=0;
	for(i=n;i>0;i--) B[i]=i-1; B[0]=n;
}
// for(i=F[0];i!=0;i=F[i]) iterate on available list indexes

////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Backtrack(int i) // backtrack using dancing links
{
    if(i==n)
    {
        sol_cnt++;
//        cout<<"////////////////////////////////////"<<endl;
//        print();
//        cout<<"////////////////////////////////////"<<endl;
        return;
    }
    for(int j=F[n] ;j!=n; j=F[j])
    {
        if(valid(i, j))
        {
            Remove(j);
            change_valid(i, j);
            Backtrack(i+1);
            Restore(j);
            change_valid(i, j);
        }
    }
}
void Compute() // do necessay initializations and call Backtrack2()
{
    InitDancingLinks(n);
    initialize_arrays();
    Backtrack(0);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
//	freopen("11195.txt", "w", stdout);
	int case_num = 1;
	char t;
	cin>>n;
    while (n)
    {
        for (int i = 0; i < n; i++)
        {
            for(int j=0;j<n;j++)
            {
                cin>>t;
                bad_pos[i][j] = (t == '*');
//                board[i][j] = false;
            }
        }
        sol_cnt = 0;
        Compute();
        cout<<"Case "<< case_num++ <<": "<< sol_cnt <<endl;
        cin >> n;
    }
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
