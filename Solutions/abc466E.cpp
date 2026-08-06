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

    int popcount(int n)
    {
        return __builtin_popcountll(n);
    }

    int bitsize(int n)
    {
        if(n==0) return 0;
        else return 64 - __builtin_clzll(n);
    }

    void solve()
    {
        /*
        In this problem we can see that we have to choose only non overlapping k segments to flip such that the sum is maximized. Why? Because suppose you flipped overlapping segments than their intersection would remain unchanged as flipping it 2 times is same as not flipping at all! And so it is equivalent to flipping only their dijoint parts.

        Now how can we convert this problem to solvable form? We somehow have to to choose for all elements in which segments we have to flip them. And whatever segement we flip them in, the elments before them would be restricted to only before them. So suppose we choose not to flip the second element and we flip the third and and fourth element as the first segment. So now for k segments we have 2*k + 1 chunks as such:

        -> we do not flip (a[i] remains a[i])
        -> we flip for first time (a[i] changes to b[i])
        -> we do not flip this part (i.e. a[i] remains a[i])

        so on. 
        Now define our dp state as dp[i][j] = max score when we have processed i elments where ith elmeent is exactly in jth chunk.

        Now transitions are fairly simple as:
        dp[i][j] = (j%2==0 ? a[i] : b[i]) + max(dp[i-1][k]) 0<=k<=j. 

        We can keep track of dp[i-1][j] as we go so this would be reduced to O(N*K)

        Now the answer is max(dp[n][k]) 0<=k<=2*K+1.

        Here the important observation was to choose the state such that i-1 state is strictly before i state. Here you can easily see that if i is in x state than i-1 can only be in x-1, x-2 ... 0 state.It can't be higher than i and thus we can use such states to optimally calculate the answer.
        */
        int n, k; cin>>n>>k;
        vector<pair<int, int>> a(n);

        for(int i=0; i<n; i++)
        {
            cin>>a[i].first>>a[i].second;
        }

        vector<vector<int>> dp(n+1, vector<int>(2*k + 2, -1e18));

        dp[0][1] = 0;

        for(int i=1; i<=n; i++)
        {
            int mx = -1e18;
            for(int j=1; j<=2*k + 1; j++)
            {
                mx = max(mx, dp[i-1][j]);
                int val = ((j%2!=0) ? a[i-1].first : a[i-1].second);
                dp[i][j] = val + mx;
            }
        }

        int ans = LLONG_MIN;
        for(int i=0; i<=2*k+1; i++)
        {
            ans = max(ans, dp[n][i]);
        }

        cout<<ans<<'\n';
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