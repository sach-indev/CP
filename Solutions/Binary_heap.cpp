/*
So this is an implementation of heap(Priority queue). Here I implemented min heap but same steps can be taken to implement Maxheap or any other heap.
Also here I also do heap sort. You can see the procedure for heap sort as given below.
*/

#include <bits/stdc++.h>
using namespace std;
#define int long long
#define MAXN 100000009LL

int h[MAXN];
int n = 0;

void swap(int &x, int &y)
{
    int temp = x;
    x = y;
    y = temp;
}

//
void insert(int x)
{
    h[n] = x;
    n++;
    int i = n-1;

    while(i>0 && h[i]<h[(i-1)/2])
    {
        swap(h[i], h[(i-1)/2]);
        i = (i-1)/2;        
    }
}

int rem_min()
{
    swap(h[0], h[n-1]);
    n--;
    int i = 0;
    while(2*i+1<n)
    {
        int j = 2*i+1;
        if(j+1<n && h[j+1]<h[j]) j++;
        if(h[j]>=h[i]) break;
        else
        {
            swap(h[i], h[j]);
            i = j;
        }
    }

    return h[n];
}

int get_min()
{
    return h[0];
}

signed main()
{
    int N; cin>>N;
    vector<int> a(N);
    for(int i=0; i<N; i++)
    {
        cin>>a[i];
    }

    /*
    Basically in heap sort you add element in heap and than remove from heap. 
    */

    for(int i=0; i<N; i++)
    {
        insert(a[i]); //O(logn)
    }

    for(int i=0; i<N; i++)
    {
        a[i] = rem_min(); //O(logn)
    }

    for(int i=0; i<N; i++)
    {
        cout<<a[i]<<' ';//for increasing order.
    }
    cout<<endl;

    //This can be further improved by taking separate function for shift_up and shift_down for insert and rem_min function but I'm too lazy for that :)


    //Total Time complexity: O(NlogN)

}