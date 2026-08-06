/*This is segment tree implementation. In this particular case we find max in some range l & r;
But the user can with a little bit twiking use this code to find sum range, min in range and much more
But the basic code is as given.*/

#include <bits/stdc++.h>
using namespace std;
#define int long long

vector<int> seg;

//Here we build the segment tree and store it in a seg array when the function build() is called
//in main function.
void build(const vector<int> &a, int ind, int tl, int tr)
{
	if(tl==tr)
	{
        //base condition.
		seg[ind] = a[tl];
		return;
	}
	else
	{
		int tm = (tl+tr)/2;
        //In 1 based indexing left child = 2*inex + 1, right child = 2*index + 2.
		build(a, 2*ind + 1, tl, tm);
		build(a, 2*ind + 2, tm+1, tr);

        //While backtracking store the max for max queries
		seg[ind] = max(seg[2*ind + 1], seg[2*ind + 2]);
	}
}


//This is query function that finds the required answer in O(logN) complexity
int query(int ind, int tl, int tr, int l, int r)
{
    //If in the range than return the max value of segment i.e. seg[ind]
	if(tl>=l && tr<=r) return seg[ind];
    //If not in the range than return a very small value, typically LLONG_MIN here as min value for long long data types
	if(tl>r || tr<l) return LLONG_MIN;
	//Overlapping case. Divide the segment into two parts left and right solve the subproblems through
    //recursion. The max of these is the answer for this one.
    else
	{
		int tm = (tl+tr)/2;
		int left = query(2*ind + 1, tl, tm, l, r);
		int right = query(2*ind + 2, tm+1, tr, l, r);
		return max(left, right);
	}
}

void solve()
{
    int n; cin>>n;
    vector<int> a(n);
    //Well we are butting 1, 2, 3 etc value. iota is just a fancy c++ function that does that.
    iota(a.begin(), a.end(), 1);

    //assign space to seg as seg is empty right now. It can be easily proved that the maximum nodes in 
    //a segment tree cannot be more than 4*n. We leave this prove to readers for themselves to determine.
    seg.assign(4*n, 0);
    build(a, 0, 0, n-1);

    cout<<query(0, 0, n-1, 1, 2)<<endl;//the answer should be 3 as the array is 1, 2, 3, 4, 5 ,...so on.

    // CONCLUSION: I learnt a very useful implementation of merge tree to find the range queries of
    // nearly any type in o(logN). There are some advanced variation but I don't understand them for
    // now. Will update when I learn them.

}

signed main()
{
    int t; cin>>t;
    while(t--)
    {
        solve();
    }
}
