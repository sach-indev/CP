#include <bits/stdc++.h>
using namespace std;
#define int long long

//global variables
const static int mod = 1e9 + 7;
const static int maxn = 5*1e5 + 1;
vector<int> fact(maxn+1, 1);
//functions
int binpow(int a, int exp)
{
    if(exp==0) return 1;
    int res = 1;
    while(exp > 0)
    {
        if(exp&1) res = (res*a)%mod;
        a = (a*a)%mod;
        exp >>= 1;
    }

    return res%mod;
}

int comb(int n, int k)
{
    int res = (fact[n]*binpow(fact[n-k], mod-2))%mod;
    res = (res*binpow(fact[k], mod-2))%mod;

    return res%mod;
}

void solve()
{
    int n, m; cin>>n>>m;
    int ans = 0;

    /*
    fixing two a[m] = i and b[m] = j and than iterating over j = i, i+1 ..n and i = 1, 2, ..i
    now it reduces to stars and bars for the a sequence we have 
    x1 + x2 + x3 ... + xi-1 = m - 1 (a[m] i is fixed so distribute rest of i-1 elements)
    and x1 + x2 + ... + xn+j-1 = m-1 (b[m] = j is fixed so distribute rest of n+j-1 elments)

    Now these ways are independent so we multiply them and than sum over all values of i and j to get the answer.This is same as

    for i from 1 to n:
        for j from i to n:
          ans += comb(m+i-2, m-1)*comb(n+m-j-1, m-1);

    One elegant way to look at this is to choose a sequnce of length 2m which is non decreasing than our both sequnecs fit asf
    a1, a2, a3 ... am, bm, bm-1 .. b1 
    now accordingly this is the same as choosing 
    x1 + x2 + x3 ... xn = 2m
    which is standard stars and bars that can be solved as 
    ans = comb(2m+n-1, 2m). 

    Both of these are equivalent but the second one is better to look at.
    */
    for(int i=1; i<=n; i++)
    {
        for(int j=i; j<=n; j++)
        {
            int res = (comb(m+i-2, i-1)*comb(n+m-j-1, n-j))%mod;
            // cout<<res<<'\n';
            ans = (ans + res)%mod;
        }
    }

    cout<<ans<<'\n';
}

signed main()
{
    for(int i=1; i<=maxn; i++) fact[i] = (fact[i-1]*i)%mod;
    int tc = 1;
    // cin>>tc;
    while(tc--) solve();
}