    #include <bits/stdc++.h>
    using namespace std;
    #define int long long

    //global variables
    // const static int mod = 1e18;
    const static int maxn = 6e5 + 4; 
    vector<int> fact(maxn+1, 1), seive(maxn + 1, 1);
    vector<int> primes;
    //functions and clases

    // int binpow(int a, int exp)
    // {
    //     if(exp==0) return 1;
    //     int res = 1;
    //     while(exp > 0)
    //     {
    //         if(exp&1) res = (res*a)%mod;
    //         a = (a*a)%mod;
    //         exp >>= 1;
    //     }

    //     return res%mod;
    // }

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
        In this question there was an edge between index i and j iff gcd(a[i], a[j]) > 1.Now we just have to find the shortest path between indices s and t.

        Now we can't solve it by brute force because just to make the graph the complexity would be o(n**2). Now we try to make bipartite graph. On one side we have nodes representing the indices of array and other side we have nodes represnting prime numbers. Now we make an edge from indices node to a prime node if the prime number is in that element.As a a[i] can only have log(a[i]) different primes than our graph will only have at most nlog(max[a[i]]) edges. 

        To make it so that there is no overlap between nodes we represent our indices nodes as 2*i + 4 where the array is 0 indexed. This makes sure that we can use 2 dimensional vector for adjacency matrix. We than do bfs on this graph. The answer is dis[t]/2 + 1 because we use 2 edges to connect two guys with gcd(a[i], a[j]) > 1.
        */
        vector<int> dis(maxn + 1, -1);
        vector<vector<int>> adj(maxn + 1);
        int n; cin>>n;
        vector<int> a(n);
        for(int i=0; i<n; i++) cin>>a[i];

        int s , t; cin>>s>>t; s--; t--;

        for(int i=0; i<n; i++)
        {
            int tg = 2*i + 4;
            for(auto p : primes)
            {
                if(1LL*p*p > a[i]) break;
                if(a[i]%p==0)
                {
                    adj[tg].push_back(p);
                    adj[p].push_back(tg);
                    while(a[i]%p == 0) a[i]/=p;
                }

                if(p>a[i]) break;
            }

            if(a[i] > 1)
            {
                adj[tg].push_back(a[i]);
                adj[a[i]].push_back(tg);
            }
        }

        // for(int i=4; i<=2*(n-1) + 4; i+=2)
        // {
        //     cout<<i<<"->";
        //     for(auto j : adj[i])
        //     {
        //         cout<<j<<' ';
        //     }
        //     cout<<endl;
        // }

        deque<int> q;
        q.push_back(2*s+4);
        dis[2*s+4] = 0;
        
        vector<int> parent(maxn + 1, -1);
        
        while(!q.empty())
        {
            auto x = q.front();
            q.pop_front();
            
            for(auto i : adj[x])
            {
                if(dis[i]==-1)
                {
                    dis[i] = dis[x] + 1;
                    q.push_back(i);
                    parent[i] = x;
                }
            }
        }
        if(dis[2*t + 4]==-1) cout<<-1<<'\n';
        else
        {
            cout<<dis[2*t + 4]/2 + 1<<'\n';

            int cur = 2*t + 4;
            vector<int> ans;
            ans.push_back((cur-4)/2);
            while(parent[cur]!=-1)
            {
                cur = parent[cur];
                cur = parent[cur];
                ans.push_back((cur-4)/2);
            }

            reverse(ans.begin(), ans.end());

            for(auto i : ans) cout<<i+1<<' ';
            cout<<endl;
        }
    }

    signed main()
    {
        // for(int i=1; i<=maxn; i++) fact[i] = (fact[i-1]*i)%mod;
        seive[0] = 0;
        seive[1] = 0;
        for(int i=0; i<=maxn; i++)
        {
            if(seive[i])
            {
                for(int j=i*i; j<=maxn; j+=i)
                {
                    seive[j] = 0;
                }
            }
        }

        for(int i=0; i<=maxn; i++)
        {
            if(seive[i] == 1)
            {
                primes.push_back(i);
            }
        }

        int tc = 1;
        // cin>>tc;
        while(tc--) solve();
    }