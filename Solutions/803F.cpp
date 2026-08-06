#include <bits/stdc++.h>
using namespace std;
#define int long long

// global variables
const static int mod = 1e9 + 7;
const static int maxn = 1e5;
//  vector<int> fact(maxn+1, 1);
//  vector<int> seive(maxn + 1, 1);
//  vector<int> primes;
// functions and clases

int binpow(int a, int exp)
{
    if (exp == 0)
        return 1;
    int res = 1;
    while (exp > 0)
    {
        if (exp & 1)
            res = (res * a) % mod;
        a = (a * a) % mod;
        exp >>= 1;
    }

    return res % mod;
}

// int comb(int n, int k)
// {
//     int res = (fact[n]*binpow(fact[n-k], mod-2))%mod;
//     res = (res*binpow(fact[k], mod-2))%mod;

//     return res%mod;
// }

// class Aggstack
// {
//     public:
//     stack<pair<int, int>> st;

//     void push(int x)
//     {
//         int cur = (st.empty() ? x : max(x, st.top().second));
//         st.push(make_pair(x, cur));
//     }

//     void pop()
//     {
//         st.pop();
//     }

//     bool empty()
//     {
//         return st.empty();
//     }

//     pair<int, int> top()
//     {
//         return st.top();
//     }
// };

// class Aggqueue
// {
//     public:
//     Aggstack in, out;

//     void push(int x)
//     {
//         in.push(x);
//     }

//     void pop()
//     {
//         if(out.empty())
//         {
//             while(!in.empty())
//             {
//                 out.push(in.top().first);
//                 in.pop();
//             }
//         }

//         out.pop();
//     }

//     int op()
//     {
//         if(out.empty()) return in.top().second;
//         if(in.empty()) return out.top().second;

//         return max(in.top().second, out.top().second);
//     }
// };

int popcount(int n)
{
    return __builtin_popcountll(n);
}

int bitsize(int n)
{
    if (n == 0)
        return 0;
    else
        return 64 - __builtin_clzll(n);
}

int eq(int a, int b, int &x, int &y)
{
    if(b==0)
    {
        x = 1;
        y = 0;
        return a;
    }

    int x1, y1;
    int g = eq(b, a%b, x1, y1);
    x = y1;
    y = x1 - (a/b)*y1;
    return g;
}

pair<int, int> fib(int n)
{
    if(n==0) return {0, 1};

    auto p = fib(n>>1);
    int c = ((((p.first * p.second) % mod) * 2) % mod - (p.first * p.first) % mod + mod) % mod;
    int d = ((p.first * p.first) % mod + (p.second * p.second) % mod) % mod;

    if(n&1) return {d, (c+d)%mod};
    else return {c, d};
}

void solve()
{

    /*
    Here the basic observation was how to make a subset with gcd g. Any subset has a gcd g means that every element in it is a multiple of g. So now in the given array we count the number of elments who are a multiple of g. Let this be k. 
    
    Now for each element we have 2 options, take or not take. So total number of ways are 2^k. But one case is there when we don't take any element so we don't cosider this one and thus the total number of subsets are 2^k - 1.

    Now is this the answer? Apparently not. Suppose we have 2, 4, 8, 16 as only multiples of 2 in array. Now we see that a subset 2, 4 has gcd 2 so it is okay BUT a subset 4, 8 has gcd 4. So the formula 2^k - 1 gives us the nmber of subsets with gcd g or 2g or 3g ... or ng where ng<=mx where mx is the max elment in the array. Now Let us say that ans[i] is the number of subset with gcd exactly equal to i.

    So our final answer for ans[g] is as:

    ans[g] = 2^k - 1 - ans[2g] - ans[3g] - ans[4g] ... - ans[ng] where ng<=mx;

    Now we can take the base case as ans[mx] = 2^cnt - 1 as there is no elment greater than mx. So iterate from mx to 1. 
    Our final ans would be ans[1].
    */


    int n; cin>>n;
    vector<int> freq(maxn + 1, 0);

    int mx = LLONG_MIN;
    for(int i=0; i<n; i++)
    {
        int x; cin>>x;
        freq[x]++;
        mx = max(mx, x);
    }

    vector<int> ans(mx+1, 0);
    for(int g = mx; g>=1; g--)
    {
        int cnt = 0;
        for(int i=g; i<=mx; i+=g)
        {
            cnt += freq[i];
        }

        ans[g] = (binpow(2, cnt) - 1 + mod)%mod;
        int sub = 0;
        for(int i=2*g; i<=mx; i+=g)
        {
            sub = (sub + ans[i])%mod;
        }

        ans[g] = (ans[g] - sub + mod)%mod;
    }

    cout<<ans[1]<<'\n';
    
}

signed main()
{
    // for(int i=1; i<=maxn; i++) fact[i] = (fact[i-1]*i)%mod;
    // seive[0] = 0;
    // seive[1] = 0;
    // for(int i=0; i<=maxn; i++)
    // {
    //     if(seive[i])
    //     {
    //         for(int j=i*i; j<=maxn; j+=i)
    //         {
    //             seive[j] = 0;
    //         }
    //     }
    // }

    // for(int i=0; i<=maxn; i++)
    // {
    //     if(seive[i] == 1)
    //     {
    //         primes.push_back(i);
    //     }
    // }

    int tc = 1;
    // cin>>tc;
    while (tc--)
        solve();
}