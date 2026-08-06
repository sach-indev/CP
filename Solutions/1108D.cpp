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
    int n; cin>>n;
 
    vector<int> a(n);
    for(int i=0; i<n; i++) cin>>a[i];
 
    /*
    In this problem the key observation was that if the array has even one odd number than bob can swap this number to the second place such that we alice can only work with this number. So she would have to work with all the numbers one at a time. Now for a single number n, the answer is as:
    popcount(n) + bitsize(n) - 1 operations. So if there is even one odd number than the solution for array a is
    popcount(a[i]) + bitsize(a[i]) - 1 for all 1<=i<=n.

    Now alice can only at start make a move to increment some numbers. Now she just have to decide how much to increment. She can fix the lsb for all numbers to some value. Suppose she makes the lsb of all elments be k. To do this she has to make every element a[i] to b where b>=a[i] and b is a multiple of 2^k. 

    Now let's check the largest number 1e5 which has 17 bits so in worst case our operations to reduce are 17 + 17 - 1 i.e 33. So now this implies that k can at most be 17 as making it a multiple of 2^18 would just make the number of moves to be very large. So we have effectively restricted the number of valid values of k to set [1, 17]. We can brute force over all these values to get a valid b.

    Now there is one more caveat as the first value of b we found may not be the best value. This is becuase the the function popcount(n) + bitsize(n) - 1 is not smooth. For example popcount(127) + bitsize(127) - 1 = 11 but popcount(128) + bitsize(128) - 1 = 7. So smaller value does not imply that score would be minimum. Now luckily by the previous argument we can have maximum score as 33. That means we only have to check multiples of 2^k in range [b, b+32] because any values greater than this will have the walking cost greater than 33 at which point it is much more beneficial to just process it directly.

    So now let's say you chooos some k and some j >= a[i] and multiple of 2^k in valid interval. Now for this number the score is as:
    popcount(j) + bitsize(j) - k - 1 + (j- a[i])

    Here we do - k because k bits in front are zero and so we only consider them once and subtract their contribution from all the other numbers. j-a[i] are the moves we used in increment.

    Now take minimum of all these values for all k and we got our answer.

    */
 
    int ans = LLONG_MAX;
    for(int k=0; k<=17; k++)
    {
        int mul = (1<<k), cont = k; //cont = k to consider k only once.
        for(int i=0; i<n; i++)
        {
            int b = a[i];
            if(b%mul)
            {
                b = b + (mul - b%mul);
            }
 
            int temp = LLONG_MAX;
            for(int j=b; j<=b+32; j+=mul)
            {
                if(j==0)
                {
                    temp = min(0LL, temp); //j==0 is already reduced so no need for the formula as it would turn temp to negative.
                }
                else
                {
                    temp = min(popcount(j) + bitsize(j) - k - 1 + j - a[i], temp);
                }
            }
 
            cont += temp; //add score to total for each number
        }
 
        ans = min(cont , ans); //Take min of all the scores accross all values of k
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
    cin>>tc;
    while (tc--)
        solve();
}