// GROUP:   2
// ID:      20150257
// Assign:  04
// Assign:  CountInv
// UVA:     10810
// Name:    Mostafa Mohamed Amin
/** UVA user name : Mostafa_Amin**/

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////
long long CountInvMerge(long long* a, int n)
{

//    cout<<"merging"<<endl;
//    system("pause");
    long long* temp = new long long[n];
    int rightIndex = n / 2;
    long long inversionCount=0;
    int i=0,
        j=rightIndex,
        tempI=0;
    while((i<rightIndex && j<n))
    {
//        cout<<"C "<<a[i]<<" "<<a[j]<<endl;
        if(a[i]<=a[j])
        {
            temp[tempI++]=a[i++];
        }
        else
        {
            temp[tempI++]=a[j++];
            inversionCount+= (rightIndex - i);
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
    return inversionCount;
}

long long CountInv(long long* a, int n)
{
    long long inversionCount = 0;
    if(n > 1)
    {
        int leftSize = n / 2,
            rightSize = n - leftSize ;
//        system("pause");
//        cout<<"L - > "<<leftSize<<endl;
//        cout<<"R - > "<<rightSize<<endl;

//        for(int i=0;i<n;i++)
//            cout<<a[i]<<" ";
        inversionCount = CountInv(&a[0], leftSize);
        inversionCount += CountInv(&a[leftSize], rightSize);
        inversionCount += CountInvMerge(a, n);
    }
    return inversionCount;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
//    freopen("out.txt","w",stdout);
    int inputLength;
    cin>>inputLength;
    long long * arr ;
    while(inputLength!=0)
    {
        arr = new long long [inputLength];
        for(int i=0;i<inputLength;i++)
        {
            cin>>arr[i];
        }
        cout<<CountInv(arr,inputLength)<<endl;
        delete [] arr;
        cin>>inputLength;
    }
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
