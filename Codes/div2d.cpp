//Solution to codeforces round 1044(div 2) D named "Chicken Jockey".

#include<bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    //Taking input
	int n; cin>>n;
	vector<int> a(1);

	for(int i=0; i<n; i++)
	{
		int x; cin>>x;
		a.push_back(x);
	}

    //Making a dp array
	vector<int> dp(n+1);
	dp[0] = 0; dp[1] = a[1];

    //Interesting idea to take minimum of the result of choosing different elements to take fall damage. 
    //My own solution was 2d dp but the complexity was exponential.
	for(int i=2; i<=n; i++)
	{
		dp[i] = min(dp[i-1] + a[i]-1, dp[i-2] + a[i-1] + max(0LL, a[i]-(i-1)));
	}

	cout<<dp[n]<<'\n';

    // CONCLUSION: Here it was very useful to simply take the states that are useful and solve it in a 1d
    // dp. I think I should have seen that coming as the tree was mostly changing along the right side and 
    // the subproblems were kinda skewed conditions on one side. Need to always take care of this.
}

 
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t=1;
	cin >> t;
	while(t--){
	    solve();
	}
}