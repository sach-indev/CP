//Be slow to be fast. Think enough. Not just go in to code blindly.

/*So this can be solved by taking dp states. Let dp[a][j] be number of ways to reach a using j steps.
So dp[a, b, c][0] = 0, dp[d][0] = 1
Now we can easily see that:
dp[a][j] = dp[b][j-1] + dp[c][j-1] + dp[d][j-1]
dp[b][j] = dp[a][j-1] + dp[c][j-1] + dp[d][j-1]
dp[c][j] = dp[b][j-1] + dp[a][j-1] + dp[d][j-1]
dp[d][j] = dp[b][j-1] + dp[c][j-1] + dp[a][j-1]

so answer is dp[d][n].

HERE it is only important to know where I am and how many steps I have walked.
*/

#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod = 1000000007LL;

void solve()
{
    int n; cin>>n;
    int abc = 0, d = 1;

    for(int i=1; i<=n; i++)
    {
        //highly optimised solution by using the fact that a,b,c are symmetrical.
        int td = (abc*3LL)%mod;
        int tabc = (abc*2LL%mod + d)%mod;
        d = td;
        abc = tabc;
    }

    cout<<d<<endl;

    //Can be more optimised by using binary exponenetiation. Will update when I have studied that.
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t=1;
    //cin >> t;
    while(t--)
    {
        solve();
    }
}