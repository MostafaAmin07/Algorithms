// GROUP:   2
// ID:      20150257
// Assign:  02
// Assign:  DisjointSets
// UVA:     10608
// Name:    Mostafa Mohamed Amin
/** UVA user name : Mostafa_Amin **/
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct DisjointSets
{
	int n;
	int* parent;
	int* num_nodes;

	void Initialize(int _n)
	{
	    n=_n;
	    parent= new int[n];
	    num_nodes= new int[n];
	    for(int i=0;i<n;i++)
        {
            parent[i]=i;
            num_nodes[i]=1;
        }
	}
	void Destroy()
	{
	    n=0;
	    delete [] parent;
	    delete [] num_nodes;
	}
	int Find(int i)
	{
	    if(parent[i]!=i)
        {
            return Find(parent[i]);
        }
        return parent[i];
	}
	bool Union(int i, int j)
	{
	    int pi=Find(i),
            pj=Find(j);
        if(pi==pj)
        {
            return false;
        }
        if(num_nodes[pi] >= num_nodes[pj])
        {
            num_nodes[pi]+=num_nodes[pj];
            parent[pj]=i;
        }
        else
        {
            num_nodes[pj]+=num_nodes[pi];
            parent[pi]=j;
        }
	    return true;
	}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    int m, n, testCase, in1, in2;

	cin>>testCase;
	while (testCase--) {
		cin>>n>>m;
		DisjointSets disjointSet;
		disjointSet.Initialize(n);
		int maximum = 1;
		for (int i = 0; i < m; i++) {
			cin>>in1>>in2;
			in1--;
			in2--;
			disjointSet.Union(in1,in2);
			if (disjointSet.num_nodes[disjointSet.Find(in1)] > maximum)
				maximum = disjointSet.num_nodes[disjointSet.Find(in1)];
		}
		cout<<maximum<<endl;
	}
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
