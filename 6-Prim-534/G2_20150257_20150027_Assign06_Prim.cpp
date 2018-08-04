// GROUP:   1,2
// ID:      20150257 / 20150027
// Assign:  06
// Assign:  Prim
// UVA:     534
// Name1:   Mostafa Mohamed Amin
// Name2:   Ahmed Lotfy
// UVA ALotfy: UVA Mostafa_Amin

#include <cstdio>
#include <iomanip>
#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class Value>
struct Array
{
	int  n, sz;
	Value* arr;

	void Initialize()
	{
		sz = 1;
		n = 0;
		arr = new Value[sz];
	}
	void Destroy()
	{
		delete[] arr;
	}
	void AddLast(Value v)
	{
		if (sz == n)
		{
			sz *= 2;
			Value* new_arr = new Value[sz];
			for (int i = 0;i < n;i++)
			{
				new_arr[i] = arr[i];
			}
			delete[] arr;
			arr = new_arr;
		}
		arr[n++] = v;
	}
	void RemoveLast()
	{
	    if(n>0)
        {
            n--;
        }
	}
	Value& operator[](int i)
	{
	    if(i<n)
        {
            return arr[i];
        }
	}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Edge
{
	int		v;  // id of the adjacent node
	double	w;  // edge weight = distance between the two nodes
};

struct Node
{
	int x,y; // x and y coordinates of the node
	Array<Edge> adj;

	void Initialize()
	{
	    adj.Initialize();
	}
	void Destroy()
	{
	    adj.Destroy();
	}
};

struct Graph
{
	int n;
	Node* nodes;

	void Initialize(int _n)
	{
	    n=_n;
	    nodes = new Node[n];
	    for(int i=0;i<n;i++)
        {
            nodes[i].Initialize();
        }
	}
	void Destroy()
	{
	    for(int i=0;i<n;i++)
        {
            nodes[i].Destroy();
        }
        delete [] nodes;
	    nodes = NULL;
	}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Find the square root of "v" in "n" iterations
double Sqrt(double v, int n=100)
{
    if(v==0)
        return 0;
    double upper = v;
    double lower = 0,result=0,mid=0;
    while(n--)
    {
        mid=(upper+lower)/2;
        result= mid*mid;
        if(result-v > -.0001 && result-v < .0001)
        {
			break;
        }
        else if(result>v)
        {
            upper=mid;
        }
        else
        {
            lower=mid;
        }
    }
	return mid;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
void calculateWeight(Graph graph, int index)
{
	for (int i = 0; i < graph.n; i++)
	{
		Edge e;
		e.v = i;
		double xS = (graph.nodes[i].x - graph.nodes[index].x);
		xS *= xS;
		double yS = (graph.nodes[i].y - graph.nodes[index].y);
		yS *= yS;
		double sqr=((xS+yS)>0)?xS+yS:(xS+yS)*-1;
		e.w = Sqrt(xS + yS,1000);
		graph.nodes[index].adj.AddLast(e);
	}
}

double prim(Graph graph)
{
	//initializing arrays
	Array<double> cost;
	Array<int> prev;
	Array<bool> inSpanningTree;
	cost.Initialize();
	prev.Initialize();
	inSpanningTree.Initialize();
	for (int i = 0;i < graph.n;i++)
	{
		inSpanningTree.AddLast(false);
		cost.AddLast(graph.nodes[0].adj[i].w);
		prev.AddLast(0);
	}
	//start point
	cost[0] = 0;
	prev[0] = -1;
	for(int i=0;i<graph.n;i++)
    {
        //catching the minimum vertix
        double minimum = INT32_MAX;
        int minIndex=0;
        for(int j = 0; j < graph.n; j++)
        {
            if(!inSpanningTree[j] && cost[j] < minimum)
            {
                minimum = cost[j];
                minIndex = j;
            }
        }
        //make it in and update cost and prev
        inSpanningTree[minIndex] = true;
        for(int _i = 0; _i < graph.n; _i++)
        {
            if( !inSpanningTree[_i] && graph.nodes[minIndex].adj[_i].w <  cost[_i])
            {
                prev[_i] = minIndex;
                cost[_i] = graph.nodes[minIndex].adj[_i].w;
            }
        }
        if (minIndex ==1)
        {
            break;
        }
    }
    double maximumJumpDistance=-1;
    int index=1;
    while(prev[index]!=-1)
    {
        if(cost[index]>maximumJumpDistance)
        {
            maximumJumpDistance = cost[index];
        }
        index = prev[index];
    }
    cost.Destroy();
    prev.Destroy();
    inSpanningTree.Destroy();
    return maximumJumpDistance;
}

int main()
{
//    freopen("test.txt","w",stdout);
	int numberOfStones,counter=1;
	Graph graph;
	cin >> numberOfStones;
	while (numberOfStones > 0)
	{
		graph.Initialize(numberOfStones);
		for (int i = 0;i < numberOfStones;i++)
		{
			cin >> graph.nodes[i].x >> graph.nodes[i].y;
		}
		for (int i = 0;i < numberOfStones;i++)
		{
		 	calculateWeight(graph, i);
		}
        cout<<"Scenario #"<<counter++<<endl;
        cout<<"Frog Distance = "<<fixed<<setprecision(3)<<prim(graph)<<endl<<endl;
		cin >> numberOfStones;
	}
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
