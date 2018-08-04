// GROUP:   1,2
// ID:      20150027, 20150257
// Assign:  07
// Assign:  Dijkstra
// UVA:     10986
// Name1:   Mostafa Mohamed Amin
// Name2:   Ahmed Lotfy
// UVA ALotfy: UVA Mostafa_Amin of student

#include <cstdio>
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

template<class Elem>
struct Heap
{
	int* pos=NULL; // pos[v]=i where a[i].v=v, otherwise pos[v]=-1
	Array<Elem> a;
	bool (*IsBefore)(Elem&, Elem&);

	void Initialize(bool (*_IsBefore)(Elem&, Elem&), int n) // n is required to allocate and initialize pos[]
	{
	    IsBefore=_IsBefore;
        a.Initialize();
        pos = new int[n];
        for(int i=0;i<n;i++)
        {
            pos[i]=-1;
        }
	}
	void Destroy()
	{
	    if(pos!=NULL)
            delete [] pos;
	    a.Destroy();
	}
	/** just for debugging **/
	void print()
	{
	    for(int i=0;i<a.n;i++)
        {
            cout<<a[i];
            if(Child(i)<a.n)
            {
                cout<<" +> "<< a[Child(i)];
                if(Child(i)+1<a.n)
                    cout<<" +> "<< a[Child(i)+1]<<endl;
            }
            cout<<endl;
        }
	}
	int Child(int i)
	{
	    return 2*i+1;
	}
	int Parent(int i)
	{
	    return (i-1)/2;
	}
	Elem GetFirst()
	{
        return a[0];
	}
	Elem RetrieveFirst()
	{
        Elem toReturn = a[0];
        a[0] = a[a.n-1];
        pos[a[a.n-1].v]=-2;
        pos[a[0].v]=0;
        a.RemoveLast();
        MoveDown(0);
        return toReturn;
	}
	void Add(Elem e)
	{
        a.AddLast(e);
        //pos
        pos[e.v]=a.n-1;
        MoveUp(a.n-1);
	}
	void MoveUp(int ind)
	{
        if(ind==0)
        {
            return;
        }
        int parentIndex = Parent(ind);
        if(IsBefore(a[ind],a[parentIndex]))
        {
            Elem temp = a[parentIndex];
            //pos
            int tempPos = pos[a[parentIndex].v];
            pos[a[parentIndex].v]=pos[a[ind].v];
            pos[a[ind].v]=tempPos;

            a[parentIndex] = a[ind];
            a[ind] = temp;
            MoveUp(parentIndex);
        }
	}
	void MoveDown(int ind)
	{
        int leftChildIndex = Child(ind);
        if(leftChildIndex>=a.n)
        {
            return;
        }
        int minimumIndex = ind;
        if(IsBefore(a[leftChildIndex],a[ind]))
        {
            minimumIndex = leftChildIndex;
        }
        int rightChildIndex = leftChildIndex + 1;
        if(rightChildIndex < a.n && IsBefore(a[rightChildIndex],a[leftChildIndex]) && IsBefore(a[rightChildIndex],a[ind]))
        {
            minimumIndex = rightChildIndex;
        }
        if(minimumIndex != ind)
        {
            Elem temp = a[minimumIndex];
            //pos
            int tempPos = pos[a[minimumIndex].v];
            pos[a[minimumIndex].v]=pos[a[ind].v];
            pos[a[ind].v]=tempPos;

            a[minimumIndex] = a[ind];
            a[ind] = temp;
            MoveDown(minimumIndex);
        }
	}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Edge
{
	int		v;
	int		w;
};

struct Node
{
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

bool IsBefore(Edge& a, Edge& b)
{
	return a.w<b.w;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class T>
T Input(std::istream& is){
  T result;
  is >> result;
  return result;
}

long long dijkestra(Graph graph, int edges, int start, int finish)
{
    Heap<Edge> heap;
//    Array<int> prev;
//    Array<bool> inPath;
    Array<long long> cost;
//    prev.Initialize();
    cost.Initialize();
    heap.Initialize(IsBefore,edges);
//    inPath.Initialize();

    for(int i=0;i<graph.n;i++)
    {
//        prev.AddLast(-1);
        cost.AddLast(INT32_MAX);
//        inPath.AddLast(false);
    }

//    inPath[start]=true;
    cost[start]=0;

    for(int i=0;i<graph.nodes[start].adj.n;i++)
    {
        heap.Add(graph.nodes[start].adj[i]);
        cost[graph.nodes[start].adj[i].v] = graph.nodes[start].adj[i].w;
        cout<<" "<<graph.nodes[start].adj[i].w<<endl;
//        prev[graph.nodes[start].adj[i].v] = start;
//        cout<<"From "<<start<<" >>> "<<graph.nodes[start].adj[i].v<<" -c- "<<cost[graph.nodes[start].adj[i].v]<<endl<<endl;
    }

    int minIndex = start;
    Edge temp;
    while(heap.a.n)
    {
        temp = heap.RetrieveFirst();
        cout<<temp.v<<" "<<temp.w<<endl;
//        prev[temp.v] = minIndex;
//        cout<<"From "<<prev[temp.v]<<" <<< "<<temp.v<<" -w- "<<cost[temp.v]<<endl<<endl;
//        cout<<"============================================================="<<endl;
        minIndex = temp.v;
        for(int i=0;i<graph.nodes[minIndex].adj.n;i++)
        {
            int to = graph.nodes[minIndex].adj[i].v
                , weight = graph.nodes[minIndex].adj[i].w;

//            cout<<"CONDITION: to: "<<to<<" W: "<<weight<<" \ncostf: "<<cost[minIndex]<<" total "<<cost[minIndex]+weight<<" costto: "<<cost[to]<<endl;
            if(cost[minIndex]+weight < cost[to])
            {
                cost[to] = cost[minIndex] + weight;
                cout<<"CostTO "<<cost[to]<<endl;
//                cout<<"add From "<<minIndex<<" -> "<<to<<" -w- "<<cost[to]<<endl<<endl;
//                cout<<">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"<<endl;
                heap.Add(graph.nodes[minIndex].adj[i]);
//                prev[to] = minIndex;
            }
        }
    }
    long long total_cost=cost[finish];
//    prev.Destroy();
    cost.Destroy();
    heap.Destroy();
//    inPath.Destroy();
    return total_cost;
}

int main()
{
//    freopen("10986.txt","w",stdout);
    int testCases,n,m,s,t;
    Graph graph;
    cin>>testCases;
    for(int i=0;i<testCases;i++)
    {
        cin>>n>>m>>s>>t;
//        cout<<n<<" "<<m<<" "<<s<<" "<<t<<endl;
        if(m==0)
        {
            cout<<"Case #"<<i+1<<": unreachable"<<endl;
            continue;
        }
        else
        {
            graph.Initialize(n);
            for(int j=0;j<m;j++)
            {
                Edge e;
                int i1,i2,w;
                cin>>i1>>i2>>w;
                e.v=i2;
                e.w=w;
                graph.nodes[i1].adj.AddLast(e);
                e.v=i1;
                graph.nodes[i2].adj.AddLast(e);
            }
            long long distance=dijkestra(graph,m,s,t);
            if(distance==INT32_MAX)
            {
                cout<<"Case #"<<i+1<<": unreachable"<<endl;
            }
            else
            {
                cout<<"Case #"<<i+1<<": "<<distance<<endl;
            }
        }
        graph.Destroy();
    }
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
