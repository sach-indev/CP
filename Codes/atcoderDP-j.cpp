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
    Actually the recursive formula here is a reduced one which comes from the defination of law of total expectation. It is basically related to markov chain where we try to model our situation as states and it has the property that we only need a couple of states 1 step after to calculate the expected value.

    Now the law is as:
    E(E(x|y)) = E(x). That's it. It basically means that average of some weighted disjoint events is same as the average of whole event. So in our case, we define our state as such

    E[x][y][z] = Expected steps to empty all plates when we have x plate with 1 sushi, y plate with 2 sushi and z plate with 3 sushi. Now let's see our options:

    Case 1: Take a sushi from plate with only one sushi.
    Now this means the number of steps we have to take are E[x-1][y][z]*x/n where n is the total number of sushi's availabe.

    case 2: Take a sushit from plate with 2 sushi.
    so this will contribute E[x+1][y-1][z]*y/n. This is because the number of plates with one sushi has increased after this step.

    case 3: Take as sushi from plate with 3 sushi.
    similar to previous case its E[x][y+1][z-1]*z/n. 

    case 4: We choose and empty box so no sushi for us.
    so we repeat the same state thus contribution is E[x][y][z]*(n-x-y-z)/n

    Now our number of steps do increase by 1 thus the whole equation is as:
    E[x][y][z] = E[x-1][y][z]*x/n + E[x+1][y-1][z]*y/n + E[x][y+1][z-1]*z/n 
    + E[x][y][z]*(n-x-y-z)/n.

    Rearranging to solve for E[x][y][z], we get:
    E[x][y][z] = (n + x*E[x-1][y][z] + y*E[x+1][y-1][z] + z*E[x][y+1][z-1])/(x+y+z);

    We have to start our outer loop from z because in last transition we need z-1. Now in second transition we need y-1 and y+1 but notice y+1 is with z-1 so it is already calculated! similarly we need x-1 and x+1 but x+1 has y-1 which we have already calculated by taking it as second loop. 

    The point is to look at the transiton and ensure that they work in such a way we have calculated all the previous states needed to calculate the current state. In here all the transtion of y is dependent on z and x is depened on y so loop order is first the one which is not dependent on anyone i.e. z than y and than x.
    */



    int n; cin>>n;
    vector<int> freq(3, 0);
    for(int i=0; i<n; i++)
    {
        int x; cin>>x;
        freq[x-1]++;
    }

    vector<vector<vector<double>>> E(n+1, vector<vector<double>>(n+1, vector<double>(n+1, 0.0)));

    E[0][0][0] = 0.0;

    for(int k=0; k<=n; k++)
    {
        for(int j=0; j<=n; j++)
        {
            for(int i=0; i<=n; i++)
            {
                if(i==0 && j==0 && k==0) continue;
                if(i+j+k > n) continue;

                double e = n;

                if(i>0) e += i*E[i-1][j][k];
                if(j>0) e += j*E[i+1][j-1][k];
                if(k>0) e += k*E[i][j+1][k-1];

                E[i][j][k] = e/(i+j+k);
            }
        }
    }

    // for(int i=0; i<=n; i++)
    // {
    //     for(int j=0; j<=n; j++)
    //     {
    //         for(int k=0; k<=n; k++)
    //         {
    //             if(i+j+k <= n) cout<<E[i][j][k]<<'\n';
    //         }
    //     }
    // }

    cout<<fixed<<setprecision(10)<<E[freq[0]][freq[1]][freq[2]]<<endl;
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