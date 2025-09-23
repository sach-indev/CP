/*
So this question is so beautiful. Here we have to efficiently calculate how many times does an integer comes in all hte set. So we first create an array
c and we intialize it with 0. Now let us given a set l & r, we simply do c[l]++
and c[r]--. Why you ask? Well the first c[l]++ says that all the integers such 
that i>=l are in this set atleast one. So when we, you know prefix sum the c array due to this i we know how many elements have come in this set. But now this contribution cannot go on forever. Otherwise we will continue to propogate. So to stop this propogation we decrement c[r]--. Now if we take prefix sum the +1 is cancelled by this -1. Damn this is so beautiful.

Keep track that what we are doing (that is checking contribution) is essentially push dp or more generally recursive thinking to find the contribution and all of the 1st element into another. 

This explaination is kinda messy so I will update it whenever I get a more neat explaination.
*/


#include <bits/stdc++.h>
using namespace std;
#define int long long

vector<int> c(2000010, 0);

void solve()
{
    int a, b; cin>>a>>b;
    cout<<c[b] - c[a-1]<<'\n';
}
  
signed main()
{
	ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k, q;
	cin>>n>>k>>q;

    for(int i=0; i<n; i++)
    {
        int x, y; cin>>x>>y;
        c[x]++; c[y+1]--;
    }

    for(int i=1; i<=200000; i++) c[i] = c[i-1] + c[i];

    for(int i=1; i<=200000; i++)
    {
        if(c[i]>=k) c[i] = 1;
        else c[i] = 0;
    }

    for(int i=1; i<=200000; i++) c[i] = c[i-1] + c[i];

    while(q--)
    {
        solve();
    }
}


//conclusion: Think recursively. Think differently.