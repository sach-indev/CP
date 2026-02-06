//Be slow to be fast. Think enough. Not just go in to code blindly.

#include<bits/stdc++.h>
using namespace std;
#define int long long
const static int mod = 998244353LL;

#include <bits/stdc++.h>
using namespace std;

/*In this problem you have a kinda constrained operations. So you can have prefix of positive numbers and than some suffix of negative numbers as you can only remove positive numbers from prefix as removing them from suffix is well destroyes the whole array.

So you check the value of prefix + suffix for whole array. This can be done in o(n) by precomputation.*/

void solve()
{
    int n; cin>>n;
    vector<int> a(n);

    for(int i=0; i<n; i++) cin>>a[i];

    vector<int> p(n), s(n);
    if(a[0]>0) p[0] = a[0];
    if(a[n-1]<0) s[n-1] = -a[n-1];

    for(int i=1; i<n; i++)
    {
        p[i] = p[i-1];
        if(a[i]>0) p[i] += a[i];
    }

    for(int i=n-2; i>=0; i--)
    {
        s[i] = s[i+1];
        if(a[i]<0) s[i] -= a[i];
    }

    int ans = 0;
    for(int i=0; i<n; i++)
    {
        ans = max(ans, p[i] + s[i]);
    }

    cout<<ans<<'\n';
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tc=1;
    cin >> tc;
    while(tc--)
    {
        solve();
    }
}


//Bonus : There's a DP Solution but its not within my paygrade. The solution
//is pasted here though for future references.

/*The choice of which element to pick—and thus which part of the array remains—is inherently sequential. Moreover, the type of move (left or right) determines which segment of the array is still “alive” for future moves. Hence, we must track two distinct “states”:

Right-turn State: The last move was positive, so the remaining part of the array is the suffix.
Left-turn State: The last move was negative, so the remaining part of the array is the prefix.
Dynamic Programming Formulation I define a DP table where:

dp[i][0] is the maximum coins we can obtain by optimally processing the first i+1 elements if the last move was a right-turn (i.e., ended with a positive element).
dp[i][1] is the maximum coins we can obtain by optimally processing the first i+1 elements if the last move was a left-turn (i.e., ended with a negative element).
Transitions: For each subsequent element (from i = 1 to n-1), the idea is to extend the best sequence so far:

If a[i] is positive (right move): You can only “append” a positive move if the previous state was already in a right-turn configuration (since a positive move always discards the left side). Therefore, you update:
dp[i][0] = dp[i-1][0] + a[i];
here note that we can still consider the case that in the last turn we selected the right turn and so by selecting the previous element first and then selecting this we can consider the dp[i-1][0] state also.

2.If a[i] is negative (left move): A negative move can be taken regardless of whether the previous move was a left-turn or a right-turn, since you “cut” from the other end. Hence, you take the best of both states from the previous step and add |a[i]|:

dp[i][1] = max(dp[i-1][0], dp[i-1][1]) + abs(a[i]);
Often, we also carry forward the best values from the previous state if not taking the current element yields a better result. This is why the implementation starts each iteration by copying the previous dp state.*/
