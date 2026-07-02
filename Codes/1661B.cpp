#include <bits/stdc++.h>
using namespace std;
#define int long long

//global variables
// const static int mod = 1e9 + 7;
// const static int maxn = 1e6 + 1;
// vector<int> fact(maxn+1, 1), seive(maxn + 1, 1);
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

int n, m = 32768;

vector<pair<int, int>> d = {{1, 0}, {0, -1}, {0, 1}, {-1, 0}};
vector<int> dis(m), vis(m, 0);

void bfs(int src)
{
    deque<int> q;
    q.push_back(src);
    vis[src] = 1;
    dis[src] = 0;
    while(!q.empty())
    {
        int x = q.front();
        q.pop_front();

        if(!vis[(x - 1 + m)%m])
        {
            dis[(x - 1 + m)%m] = dis[x] + 1;
            vis[(x - 1 + m)%m] = 1;
            q.push_back((x-1+m)%m);
        }

        if(x%2==0)
        {
            int p = x/2;
            if(!vis[p])
            {
                vis[p] = 1;
                dis[p] = dis[x] + 1;
                q.push_back(p);
            }

            p += m/2;
            if(!vis[p])
            {
                vis[p] = 1;
                dis[p] = dis[x] + 1;
                q.push_back(p);
            }
        }
    }
}

void solve()
{
    cin>>n;
    vector<int> a(n);
    for(int i=0; i<n; i++) cin>>a[i];

    /*
    Here the unique thing is we have to make a graph from (u, v) such that there is transitions as:
    v = (u+1)modm
    v = (u*2)modm

    ans each edge (u, v) has weight 1. So we can start from each u, do a dfs over all v until we reach 0. Than this is the minimum distance. But this approach gives tle as dfs is n**2 and do it over n nodes make it n**3.

    Can we do better? Notice that if we reverse all the edges of this graph i.e. we want to follow the reverse path from 0 to all the edges. But the rules shold be same as transformation we were provided just reversed. So now for the first rule:
    v = (u+1)modm 
    means that
    v = u+1 + km for all k>0;
    now this implies
    u = v-1-km
    to remove the negative sign we do
    u = v-1-km.
    so u = v-1+m and to keep in smaller than m mod this value.

    Similar reasoning for step 2 gives
    v = u*2 + km for all k>0
    now we have to find valid values of u. Now as m = 2^15 so v has to be even. If v is odd than well 
    there are no such u. So let's say v is even.
    Than
    u*2 = v - km.
    Now
    u = (v-km)/2
    implying u = v/2, (v+m)/2

    why? v/2 is obvious and (v+m)/2 is because maybe this guy is also smaller than m than we have to consider it also.
    Actually we have to but I'm not clear why this works for now myself.

    

    */

    bfs(0);

    for(int i=0; i<n; i++)
    {
        cout<<dis[a[i]]<<' ';
    }

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

    int tc = 1;
    // cin>>tc;
    while(tc--) solve();
}