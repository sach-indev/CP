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

pair<int, int> prs[6000005];


void solve()
{

    /*
    This is a good question. Here simply see that the max sum can be at most 5 x 1e6 because a[i] <= 2.5 x 1e6. Ok so now let's see cases.

    case 1: We have 4 or more occurences of any number. Than we got our answer.

    case 2: We have at least 2 guys with 2 or more occurences. Than also we got answer.
    
    case 3: We have at only 1 guy with 2 or more occurences. let this guy be c. So now we can check by two pointers with sorting whether there exists u<c<v such that u + v = 2*c. If there is such u and v than we got our answer. Other wise we move to last case.

    case 4: So all the other methods failed. Now we remove all the extra occurences keeping only 1 occurence of each elment. Ok so now all elements are distinct.

    Now lets say we have something like 5 x 1e6 boxes numbered as such. So now you put each pair into a box with that sum. So now you know that from n array elments you can make n*(n-1)/2 pairs. So now to fill these boxes once you have to say process first k guys that is 
    k*(k-1)/2 = 5 x 1e6 
    that gives k = 4000 more or less. So after processing with 4000 elements now we have more pairs so one of the pair has to go in a box that already has pair that is we got our answer.

    So in conclusion, we will find our answer in at most 4000 iterations even in worse cases. Either that or n*(n-1)/2 < 5x1e6 i.e the size of the array is smaller than 4000 so we didn't find any guy (or we did and we printed it out). 

    Anyway so the effective complexity is O(min(n*n, n + c)) which fits.
    */
    
    
    int n; cin>>n;
    vector<int> a(n);
    for(int i=0; i<n; i++) cin>>a[i];

    for(int i=0; i<n; i++)
    {
        for(int j=i+1; j<n; j++)
        {
            auto [x, y] = prs[a[i] + a[j]];

            if(x!=i+1 and x!=j+1 and y!=i+1 and y!=j+1 and x!=0 and y!=0)
            {
                cout<<"YES\n";
                cout<<i+1<<' '<<j+1<<' '<<x<<' '<<y<<'\n';
                return;
            }

            prs[a[i] + a[j]] = {i+1, j+1};
        }
    }

    cout<<"NO\n";
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