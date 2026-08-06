//Includes
#include <bits/stdc++.h>
using namespace std;
 
//Macros
#define int long long
 
//global scope
const int inf = 1e18;
const int MAXN = 1e6;

vector<int> isprime(MAXN + 1, 1);
vector<int> prime;
vector<int> b;

//classes
class matrix
{
    public: 
    int n, m;

    static const int mod = LLONG_MAX;
    vector<vector<int>> a;

    matrix() : n(0), m(0) {}

    matrix(int r, int c) : n(r), m(c), a(n, vector<int>(m, 0)) {}

    matrix(int r, int c, int v) : n(r), m(c), a(n, vector<int>(m, v)) {}

    vector<int>& operator[](int i)
    {
        return a[i];
    }

    const vector<int>& operator[](int i) const
    {
        return a[i];
    }

    matrix operator+(const matrix& other) const
    {

        if(n != other.n || m != other.m)
        {
            throw invalid_argument("Dimensions not equal.\nExiting...");
        }

        matrix res(n, m);

        for(int i=0; i<n; i++)
        {
            for(int j=0; j<m; j++)
            {
                res[i][j] = (a[i][j] + other[i][j])%mod;
            }
        }

        return res;
    }

    matrix operator*(const matrix& other) const
    {
        if(m != other.n)
        {
            throw invalid_argument("Columns of first != row of second.\nExiting...");
        }

        matrix res(n, other.m);

        for(int i=0; i<n; i++)
        {
            for(int k = 0; k<m; k++)
            {
                for(int j=0; j<other.m; j++)
                {
                    res[i][j] = (res[i][j] + a[i][k]*other[k][j])%mod;
                }
            }
        }

        return res;
    }

    static matrix identity(int n)
    {
        matrix I(n, n);

        for(int i=0; i<n; i++)
        {
            I[i][i] = 1;
        }

        return I;
    }
    
};
 
//functions

matrix binpow(matrix A, int exp)
{

    if(A.n != A.m)
    {
        throw invalid_argument("matrix not square.\nExiting...");
    }

    matrix res = matrix::identity(A.n);

    while(exp > 0)
    {
        if(exp&1) res = res*A;

        A = A*A;

        exp >>= 1;
    }

    return res;
}

int binpow(int a, int exp)
{
    int res = 1;

    while(exp>0)
    {
        if(exp&1) res = res*a;
        a = a*a;
        exp>>=1;
    }

    return res;
}

//Solution Per Test Case
void solve()
{
    /*
    DP here is n**2 as we have to think about how many plates we have eaten till than and the current plate.

    The greedy idea was that first of all we can eat a plate in k+1 minutes. So we will have a total of max n/k+1 plates that we can eat. 

    Now let's say the remaining time at any point is t. Than you can only eat t/k+1 plates at after that time. So say like t = n than n-1 than n-2 and so on.

    Now if you can take say 5 plates than you will pick the first plate from the set of elements till t%k+1 == 0. Why? Let's take n = 10 and k = 2. Now we see the remaining time as:

    10, 9, 8, 7, 6, 5, 4, 3, 2, 1
    
    Now see the dividing by 3. We see that 10/3 = 3, 9/3 = 3 but 8/3 = 2.So after and at 8 min remaining you can only pick 2 plates. That means you have to pick a plate at the point 9/3 = 3. So we observe that this is the point where t%k+1==0.

    So now the solution reduces to this simple algorithm:
    ->Maintain a maxheap of elements. 
    ->at every minute check whether t%k+1 == 0.
    ->If yes take the maximum from heap and add to answer. 
    -> if no continue.

    The time issue constraints us to pick an element before certain times. And we do that because if we don't than we won't be able to pick the max number of items and won't be able to get max deliciousness.
    */
    int n, k; cin>>n>>k;
    priority_queue<int> q;

    int ans = 0;
    for(int i=0; i<n; i++)
    {
        int x; cin>>x;
        q.push(x);
        if((n-i)%(k+1) == 0)
        {
            ans += q.top();
            q.pop();
        }
    }

    cout<<ans<<'\n';
}
 
//Main function
signed main()
{
    int tc = 1;
    cin>>tc;  
    while(tc--) solve();
}