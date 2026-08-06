//Be slow to be fast. Think enough. Not just go in to code blindly.

/*A tricky question involving identification of predicate function.
I solved it using binary search but it can supposedly be solved in o(n)I for once cannot fathom that solution and so this is the best I can do.*/

#include<bits/stdc++.h>
using namespace std;
#define int long long
static const int mod = 69696LL;

void solve()
{
    int n, m; cin>>n>>m;
    vector<vector<int>> v(n+1, vector<int>(26, 0LL));
    vector<int> dp(26, 0LL);

    for(int i=1; i<=n; i++)
    {
        string s; cin>>s;
        for(const auto &j : s)
        {
            v[i][j-'A']++;
            dp[j-'A']++;
        }
    }

    auto f = [&](int k, int l)
    {
        for(int i=0; i<26; i++)
        {
            if(dp[i]*m - m*v[l][i] < k*dp[i] - (k-1)*v[l][i]) return false;
            //To follow the given condition total sum*m without l included should be smaller than total sum*k + single occurence of l included should return false immediately
        }

        return true;
    };

    for(int i=1; i<=n; i++)
    {
        int tl = -1LL, tr = 500001LL;
        while(tr - tl > 1)
        {
            int tm = tl + (tr - tl)/2;
            if(f(tm, i)) tl = tm;
            else tr = tm;
        }

        cout<<(tl!=-1 ? tl : -1)<<' ';
    }
}
 
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tc=1;
    // cin >> tc;
    while(tc--)
    {
        solve();
    }
}