#include <bits/stdc++.h>
#include <bit>
using namespace std;
#define int long long

// global variables
const static int mod = 998244353;
const static int maxn = 20;
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

void solve()
{
    int a, b, d; cin>>a>>b>>d;
    int k = 0;

    a |= b;
    if(a%d==0) return void(cout<<a<<'\n');
    while(a%2==0 && d%2==0)
    {
        a = a/2;
        d = d/2;
        k++;
    }
    if(a%2==1 && d%2==0) return void(cout<<-1<<'\n');

    /*

    Now we know ans = 2^k((p+1)*(2^(30-k)) - 1) such that this is divisible by (2^k)*d
    Now we got our congurence equation:
    (p+1)2^(30-k) = 1mod(d)

    rewriting as p+1 as X, 2^(30-k) as a, we get
    ax = 1mod(d)

    or ax = dy + 1 i.e ax leaves 1 remainder after dividing by d.
    so we can say ax + dy = 1 for some integer y, (we can ignore negative sign and y can be any integer)

    as a is a power of 2 and lsb of d is 1 so gcd(a, d) = 1. Thus it can be solved by extended euclid.
    */

    int A = (1LL<<(30-k)), B = d, x, y;
    eq(A, B, x, y);

    x = (x%d + d)%d;

    //now we got x = p+1. Answer is (x<<(30-k)-1)*(1<<k)

    cout<<((x<<(30-k)) - 1)*(1LL<<k)<<'\n';
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
    cin>>tc;
    while (tc--)
        solve();
}