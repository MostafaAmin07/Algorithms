// GROUP:   2
// ID:      20150257
// Assign:  05
// Assign:  Kruskal
// UVA:     11631
// Name:    Mostafa Mohamed Amin
/** UVA use name : Mostafa_Amin **/
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

template<class Type>
void Merge(Type* a, int n, bool (*IsBefore)(Type& a, Type& b))
{

//    cout<<"merging"<<endl;
//    system("pause");
    Type* temp = new Type[n];
    int rightIndex = n / 2;
    int i=0,
        j=rightIndex,
        tempI=0;
    while((i<rightIndex && j<n))
    {
//        cout<<"C "<<a[i]<<" "<<a[j]<<endl;
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
//    for(int i=0;i<n;i++)
//        cout<<a[i]<<" ";
//    cout<<endl<<"----------"<<endl;
//    for(int i=0;i<n;i++)
//        cout<<temp[i]<<" ";
//    cout<<endl<<"----------"<<endl;
    for(int i=0;i<n;i++)
    {
        a[i]=temp[i];
//        cout<<temp[i]<<endl;
    }
//    cout<<"End Merging"<<endl;
    delete[] temp;
}

template<class Type>
void MergeSort(Type* a, int n, bool (*IsBefore)(Type& a, Type& b))
{
    if(n > 1)
    {
        int leftSize = n / 2,
            rightSize = n - leftSize ;
//        system("pause");
//        cout<<"L - > "<<leftSize<<endl;
//        cout<<"R - > "<<rightSize<<endl;

//        for(int i=0;i<n;i++)
//            cout<<a[i]<<" ";
        MergeSort(&a[0], leftSize, (*IsBefore));
        MergeSort(&a[leftSize], rightSize, (*IsBefore));
        Merge(a, n, (*IsBefore));
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Edge
{
	int u, v;
	int w;
};

bool IsBeforeEdge(Edge& a, Edge& b)
{
	return a.w<b.w;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
//    freopen("out.txt","w",stdout);
    int m,n,u,v,w,result=0;
    DisjointSets dSet;
    Edge * graph;
    cin>>m>>n;
    while(m!=0)
    {
        graph = new Edge[n];
        dSet.Initialize(m);
        for(int i=0;i<n;i++)
        {
            cin>>u>>v>>w;
            graph[i].u=u;
            graph[i].v=v;
            graph[i].w=w;
        }
        MergeSort(graph,n,IsBeforeEdge);
        result=0;
        for(int i=0;i<n;i++)
        {
            if(dSet.Find(graph[i].u)!=dSet.Find(graph[i].v))
            {
                dSet.Union(graph[i].u,graph[i].v);
            }
            else
            {
                result+= graph[i].w;
            }
        }
        cout<<result<<endl;
        cin>>m>>n;
        dSet.Destroy();
        delete [] graph;
    }
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
