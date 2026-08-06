/*
A very lovely problem. Here we check whether which group is the largest. Let it be f1.
Now we can have n-f1 people who can pair with f1. Now we have two cases:
Case 1: f1 > n-f1
    Now in this case since we can pair each element of f1 with other elements so we do so. Than the only elements left unpaire are f1 - (n-f1) which is our answer.

Case 2: f1 <= n-f1
    Now this part is tricky. We see an obvious thing here that we can take the two largest groups and remove 1 element each from them. As we are removing 2 elements on each step so the parity will remain invariant. Also inductively we can see that if the point is valid for all groups <N than somehow it's obvious that we can just do similar stuff and suppose we took f1 & f2 and did the operation that either a) we have a new largest group but the condition fmax <= n - fmax still holds or b) f1 is still the largest group so the condition still holds. Hence by proof of induction, we have proved the answer is n%2 where n is the number of elments.
*/

#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n; cin>>n;
    map<int, int> mp;
    for(int i=0; i<n; i++)
    {
        int x; cin>>x;
        mp[x]++;
    }

    int mx = 0;
    for(auto &i : mp) mx = max(mx, i.second);

    cout<< (mx>n-mx ? mx-(n-mx) : n%2)<<endl;
}
  
signed main()
{
	ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t=1;
	cin>>t;
    while(t--)
    {
        solve();
    }
}

//conclusion: Inductive proofing is the way to go. It helps you think and also correct your solution so that you are not running around the problem like a headless chicken.