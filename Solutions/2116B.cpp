//Be slow to be fast. Think enough. Not just go in to code blindly.

#include<bits/stdc++.h>
using namespace std;
#define int long long
const static int mod = 998244353LL;
vector<vector<int>> g;
vector<int> vis;

void solve()
{
    int n; cin>>n;
    vector<int> p(n), q(n);
    
    for(int i=0; i<n; i++) cin>>p[i];
    for(int i=0; i<n; i++) cin>>q[i];

    vector<int> mxp(n, 0), mxq(n, 0);

    //The array store max prefix. It is redundant but i find it cool and structured.
    mxp[0] = 0; mxq[0] = 0;
    for(int i=1; i<n; i++)
    {
        mxp[i] = (p[i] > p[mxp[i-1]] ? i : mxp[i-1]);
        mxq[i] = (q[i] > q[mxq[i-1]] ? i : mxq[i-1]);
    }

    //Can also calculate 2 raise to power i % mod in o(1). This is because
    //m*n%mod = (m%mod*n%mod)%mod. So no need for this function which calculates in o(logn)
    auto f = [](int a, int b)
    {
        int x=2, res1=1, res2 = 1;

        while(a>0)
        {
            if(a&1) res1 = (res1*x)%mod;
            a = a>>1;
            x = (x*x)%mod;
        }

        x = 2;
        
        while(b>0)
        {
            if(b&1) res2 = (res2*x)%mod;
            b = b>>1;
            x = (x*x)%mod;
        }

        return (res1 + res2)%mod;
    };

    vector<int> a(n);
    for(int i=0; i<n; i++)
    {
        if(p[mxp[i]] > q[mxq[i]]) a[i] = f(p[mxp[i]], q[i - mxp[i]]);
        else if(p[mxp[i]] < q[mxq[i]]) a[i] = f(p[i-mxq[i]], q[mxq[i]]);
        else
        {
            if(q[i-mxp[i]] > p[i-mxq[i]]) a[i] = f(p[mxp[i]], q[i-mxp[i]]);
            else a[i] = f(p[i-mxq[i]], q[mxq[i]]);
        }
    }

    for(int i=0; i<n; i++) cout<<a[i]<<' ';
    cout<<'\n';
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