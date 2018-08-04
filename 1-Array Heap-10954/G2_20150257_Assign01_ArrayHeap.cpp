// GROUP:   2
// ID:      20150257
// Assign:  01
// Assign:  ArrayHeap
// UVA:     10954
// Name:    Mostafa Mohamed Amin
// UVA Username: Mostafa_Amin

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

template<class Elem>
struct Heap
{
	Array<Elem> a;
	bool (*IsBefore)(Elem&, Elem&);

	void Initialize(bool (*_IsBefore)(Elem&, Elem&))
	{
	    IsBefore=_IsBefore;
        a.Initialize();
	}
	void Destroy()
	{
	    a.Destroy();
	}
	int Child(int i)
	{
	    return 2*i+1;
	}
	int Parent(int i)
	{
	    return (i-1)/2;
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
            a[minimumIndex] = a[ind];
            a[ind] = temp;
            MoveDown(minimumIndex);
        }
	}
	void Add(Elem e)
	{
        a.AddLast(e);
        MoveUp(a.n-1);
	}
	Elem GetFirst()
	{
        return a[0];
	}
	Elem RetrieveFirst()
	{
        Elem toReturn = a[0];
        a[0] = a[a.n-1];
        a.RemoveLast();
        MoveDown(0);
        return toReturn;
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
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool IsBeforeInt(int& a, int& b)
{
	return a<b;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    Heap<int> h;
    int numberOfInputs, input, total, result=0;
    h.Initialize(IsBeforeInt);
    cin>>numberOfInputs;
    while(numberOfInputs)
    {
        for(int i=0;i<numberOfInputs;i++)
        {
            cin>>input;
            h.Add(input);
        }
        while(h.a.n>1)
        {
            total=h.RetrieveFirst();
            total+=h.RetrieveFirst();
            result+=total;
            h.Add(total);
        }
        cout<<result<<endl;
        result=0;
        h.RetrieveFirst();
        cin>>numberOfInputs;
    }
    h.Destroy();
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
