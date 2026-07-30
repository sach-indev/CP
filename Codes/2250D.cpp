#include <bits/stdc++.h>
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

bool isok(vector<int> a)
{
    int n = a.size(), i = 0;
    vector<int> seen(n+2);
    while(i+1<n && a[i]<=a[i+1])
    {
        seen[a[i]] = 1;
        i++;
    }

    while(i+1<n && a[i]>=a[i+1])
    {
        i++;
        if(seen[a[i]]) return false;
    }

    return i==n-1;
}

void solve()
{
    /*
    So here the crazy observation is as that you can fix some elements. So like if you have this array a than you could only put n between c and c+1 iff
    a[c] != a[c+1], a[0]..a[c] is non decreasing, a[c+1]..a[n-1] is non increasing.

    So they form two mountains with a valley in between. Now we can see that this structure is only formed between n and n-1. No other numbers can form this structure because these two numbers will themselves ruin it if not include because they are the maximum and second maximum in the permuntation. Now it just became a standard question. You just sort the array to get a valid prefix array. Now the question reduces to:

    Given a prefix max array, find the number of permuntation which can have this array as there prefix max array.

    Now it can be solved as if a[i]!=a[i+1] we only have one way to fill this guy as it is fixed. And if a[i] == a[i+1] than we have exactly a[i] number smaller than a[i] but out of them i has been used (0 indexing here) therefore number of ways to fill this place is a[i] - i. We multiply all these values to get ans.

    Now at last we consider if we switch the places of two mountains than we have the exact same number of permuntations. So we just multiply it by 2.
    */
    
    int n; cin>>n;
    vector<int> a(n-1);

    for(int i=0; i<n-1; i++) cin>>a[i];
    int ans = isok(a);
    sort(a.begin(), a.end());

    if(a[n-2]==n) ans = 0;

    for(int i=1; i<n-1; i++)
    {
        if(a[i]==a[i-1]) ans = (ans*(a[i] - i))%mod;
    }

    cout<<(ans*2)%mod<<'\n';
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