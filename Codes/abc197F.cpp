#include <bits/stdc++.h>
using namespace std;
#define int long long

// global variables
//  const static int mod = 1e18;
//  const static int maxn = 6e5 + 4;
//  vector<int> fact(maxn+1, 1), seive(maxn + 1, 1);
//  vector<int> primes;
// functions and clases

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
    This problem is very unique. Here you have to see that whether from 1 to N node there is a path that forms a pallindrome. Now there are certain observations we can make. 

    observation 1: Imagine the process as two people starting from 1 and n. Now to get a pallindrome, there are two cases: 

    case 1: Even length. Suppose aabb be the pallindrom we get. So now the path could be

    1 2 3 4 5. Now this means that they have to end at the same vertex, in this case 3.

    case 2: Odd length. Suppose aba is the pallindrom we get. So now the path could be 
    1 2 3 4. So this  means they have to end at some vertices a, b such that there is an edge between them, in this case 1 ends at 2 and 4 ends at 3 and there is an edge between 2 and 3.

    So now the path our guys can take are constrained. Now let us take the original positions as a pair i.e. intially (1, n) is their state. Now they can move to state (a, b) only iff 
    there is and edge in original graph from 1-a and n-b and the character in them are same. Otherwise it will not form a pallindrome.

    So now we just have to make a new graph such that it has (a, b) as vertices and there is an edge between (a, b) and (c, d) only iff a-b and c-d and they have the same characters. Now how do we make this graph. First we store our original graph in and adjacency matrix.

    Now you can give unique id's to each group of (a, b) by mapping them as:
    (a, b) -> (a-1)*n + b. Why is this unique bijective mapping?
    suppose (a1 - 1)*n + b1 = (a2 - 1)*n + b2
    rearranging
    (a1 - a2)*n = (b2 - b1)

    now as 1<=b1, b2<=n therefore 
    1<=b2<=n and -n<=-b1<=-1
    adding both
    -(n-1)<=b2-b1<=n-1

    but b2 - b1 is a multiple of n and the only multiple of n between -(n-1) and (n-1) is zero. Therefore b2 - b1 = 0 or b2 = b1 and similarly a2 - a1 = 0 or a1 = a2. Thus its a bijection.

    Next
    for each vertex a from 1 to n:
        for each vertex b from 1 to n:
            for each neighbour (na, c1) of a:
                for each neighbour (nb, c2) of b:
                    check if c1 == c2
                       make an edge between them (a, b) and (na, nb)


    Now it might look O(n*n*m*m) but its not. So here the real complexity is:

    sum(deg(a)*deg(b)) for all 1<=a<=n and 1<=b<=n. We can just separate them out so that
    sum(deg(a))*sum(deg(b)) for all 1<=a<=n and 1<=b<=n.

    now sum(deg(a)) = 2*m and similarly sum(deg(b)) = 2*m.

    so total complexity becomes 2*m*2*m = 4*m*m or O(m**2) which is completely fine here.
    */

    int n, m; cin>>n>>m;
    vector<vector<pair<int,char>>> g(n+1);
    vector<tuple<int, int, char>> edges;

    for(int i=0; i<m; i++)
    {
        int a, b; char c; 
        cin>>a>>b>>c;

        g[a].emplace_back(b, c);
        g[b].emplace_back(a, c);
        edges.emplace_back(a, b, c);
    }

    vector<vector<int>> adj(n*n + 1);

    for(int a = 1; a<=n; a++)
    {
        for(int b = 1; b<=n; b++)
        {
            int id1 = (a-1)*n + b;

            for(auto &[na, c1] : g[a])
            {
                for(auto &[nb, c2] : g[b])
                {
                    if(c1 == c2)
                    {
                        int id2 = (na - 1)*n + nb;
                        adj[id1].push_back(id2);
                    }
                }
            }
        }
    }

    // for(int i=1; i<=n*n; i++)
    // {
    //     cout<<i<<"-> ";
    //     for(auto j : adj[i])
    //     {
    //         cout<<j<<' ';
    //     }
    //     cout<<endl;
    // }

    deque<int> q;
    vector<int> dis(n*n + 1, -1);

    q.push_back(n);
    dis[n] = 0;

    while(!q.empty())
    {
        auto x = q.front();
        q.pop_front();

        for(auto &i : adj[x])
        {
            if(dis[i] == -1)
            {
                dis[i] = dis[x] + 1;
                q.push_back(i);
            }
        }
    }

    // cout<<"\n\nDistances:\n\n";

    // for(int i=1; i<=n*n; i++) cout<<i<<"->"<<dis[i]<<'\n';

    int ans = LLONG_MAX;

    for(int i=1; i<=n; i++)
    {
        if(dis[(i-1)*n + i] != -1)
        {
            ans = min(ans, 2*dis[(i-1)*n + i]);
        }
    }

    for(auto [a, b, c] : edges)
    {
        int id1 = (a-1)*n + b;
        int id2 = (b-1)*n + a;

        if(dis[id1] != -1) ans = min(ans, 2*dis[id1] + 1);
        if(dis[id2] != -1) ans = min(ans, 2*dis[id2] + 1);
    }

    cout<<(ans==LLONG_MAX ? -1 : ans)<<'\n';


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