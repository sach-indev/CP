#include <bits/stdc++.h>
using namespace std;
#define int long long

// global variables
 const static int mod = 1e9 + 7;
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

void solve()
{
    /*

    This question is a one inside one question. Kinda imagine like we know about the 0/1 knapsack problem. Well here we have a knapsack inside of a knapsack. You can visualise it as being a bucket inside which we have a cup. Now we have coins and we have to find the different number of sums we can make inside the cup so that the bucket has sum exactly (target). Now the first major observation is anything inside the cup is also inside the bucket. Now we define our dp state as:

    dp[i][j][k] : whether it is possible that after processing i elments we can make a sum of j in bigger bucket and sum of k in smaller bucket.

    Base case: dp[0][0][0] = true as after processing 0 elements we can make 0 sum in both bucket and cup.

    Now we have three options:
    case1: discard coin so now dp[i][j][k] = dp[i-1][j][k] i.e. we don't use i coins so we can only make j and k by i-1 coins if it is possible.

    case2: put the coin inside the bucket but outside the cup
    so now dp[i][j][k] |= dp[i][j-c[i]][k].

    case3: put the coint inside the cup. so it is by default inside the bucket
    so now dp[i][j][k] |= dp[i][j-c[i]][k-c[i]]

    Now simply print all i such that dp[n][target][i] is true.

    Here we can optimize space by deleting the first dimension as we ever only use i-1 state so it is redundant. We just have to make sure to not use states already calculated but to use previous states for calculating current states.
    This can be done by simply going from back.

    */
    int n, w; cin>>n>>w;

    vector<int> c(n);

    for(int i=0; i<n; i++) cin>>c[i];

    vector<vector<bool>> dp(w+1, vector<bool>(w+1, false));
    dp[0][0] = true;

    for(int i=0; i<n; i++)
    {
        for(int j=w; j>=0; j--)
        {
            for(int k=w; k>=0; k--)
            {
                if(j-c[i] >= 0)
                {
                    dp[j][k] = (dp[j][k] || dp[j-c[i]][k]);
                }

                if(j-c[i]>=0 && k-c[i] >= 0)
                {
                    dp[j][k] = (dp[j][k] || dp[j-c[i]][k-c[i]]);
                }
            }
        }
    }

    vector<int> ans;
    
    for(int i=0; i<=w; i++)
    {
        if(dp[w][i]) ans.push_back(i);
    }

    cout<<ans.size()<<'\n';
    for(const auto &i : ans) cout<<i<<' ';
    cout<<endl;
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