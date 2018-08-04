// GROUP:   2
// ID:      20150257
// Assign:  03
// Assign:  Graphs
// UVA:     924
// Name:    Mostafa Mohamed Amin
/** UVA user name : Mostafa_Amin **/
#include <cstdio>
#include <cstdlib>
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

struct Node
{
	Array<int> adj;

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

template <class Type>
struct Queue
{
    /** what is f and n **/
    /** f is the current full
        n is the max size
        at least for me
     **/
	int f, n;
	Type* elems;

	void Initialize(int siz)
	{
        n=siz;
        f=0;
        elems = new Type[n];
	}
	void Destroy()
	{
        n=0;
        f=0;
        delete [] elems;
        elems = NULL;
	}
	void Add(Type t)
	{
	    if(f==n)
        {
            n*=2;
            Type* tempArr=new Type[n];
            for(int i=0;i<f;i++)
            {
                tempArr[i]=elems[i];
            }
            elems=tempArr;
        }
        elems[f++] = t;
	}
	Type Pop()
	{
        if(f>0)
        {
            Type toReturn = elems[0];
            for(int i=0;i<f-1;i++)
            {
                elems[i]=elems[i+1];
            }
            f--;
            return toReturn;
        }
	}
	Type Peek()
    {
        if(f>0)
        {
            return elems[0];
        }
	}
	int Num()
	{
        return f;
	}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    /** Variables **/
    Graph employees;
    int numOfEmployees, numOfFriends, numOfTestCases, input;
    Queue<int> q;
    Array<bool> visited;
    /** Input **/
    cin>>numOfEmployees;
    employees.Initialize(numOfEmployees);
    visited.Initialize();
    for(int i=0;i<numOfEmployees;i++)
    {
        cin>>numOfFriends;
        employees.nodes[i].Initialize();
        visited.AddLast(false);
        for(int j=0;j<numOfFriends;j++)
        {
            cin>>input;
            employees.nodes[i].adj.AddLast(input);
        }
    }
    cin>>numOfTestCases;

    /** BFS **/
    while(numOfTestCases--)
    {
        cin>>input;
        int maxBoom=-1, firstDay, currentLevel=0,
            tillNextLevel=1, tempMaxBoom=0, day=0;
        q.Initialize(numOfEmployees);
        q.Add(input);
        visited[input]=true;
        while(q.Num())
        {
//            cout<<day<<" "<<tillNextLevel<<" "<<tempMaxBoom<<" "<<safeToAdd<<endl;
            tillNextLevel--;
            int toRemove = q.Pop();
            if(tillNextLevel<=0)
            {
                day++;
                tillNextLevel=currentLevel;
                currentLevel=0;
                tempMaxBoom=0;
            }
            for(int i=0;i<employees.nodes[toRemove].adj.n;i++)
            {
//                cout<<"---> "<<day<<" "<<tillNextLevel<<" "<<tempMaxBoom<<" "<<safeToAdd<<endl;
//                cout<<"+++> "<<visited[employees.nodes[toRemove].adj[i]]<<" "<<employees.nodes[toRemove].adj[i]<<endl;
                if(!visited[employees.nodes[toRemove].adj[i]])
                {
                    currentLevel++;
                    tempMaxBoom++;
                    visited[employees.nodes[toRemove].adj[i]]=true;
                    q.Add(employees.nodes[toRemove].adj[i]);
                }
            }
            if(tempMaxBoom>maxBoom)
            {
                firstDay=day;
                maxBoom=tempMaxBoom;
            }
        }
        if(maxBoom!=0)
        {
            cout<<maxBoom<<" "<<firstDay<<endl;
        }
        else
        {
            cout<<0<<endl;
        }
        for(int i=0;i<visited.n;i++)
        {
            visited[i]=false;
        }
        q.Destroy();
    }
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
