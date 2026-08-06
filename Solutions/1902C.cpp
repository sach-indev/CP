//Includes
#include <bits/stdc++.h>
using namespace std;
 
//Macros
#define int long long
 
//global scope
const int inf = 1e18;

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
    Here we have to minimize (mx-a[i])/x for all i>=0 and i<=n;
    such that mx-a[i] is divisible by x obviously. 
    So we have to maximize x in order to minimize this sum and that can be done by taking the gcd of all mx-a[i]. Than our ans = sum(mx-a[i])/x for all 0<=i<=n-1.
    
    Now we have to introduce a new guy but as we can see introducing the new guy has to be done such that he is of the form a[i] + x*k. Now to Make sure we minimize the steps needed for this new guy to reach mx we give it the form of mx + x*k.

    Now k if +ve creates problems as mx changes to this new mx and operations to equalize increases for all. So we have to find the largest negative k such that mx + x*k does not exist in array. This will be our new guy and will take exactly abs(k) steps to reach mx. And thus we add abs(k) to our previous anwer.
    */
    
    int n; cin>>n;
    vector<int> a(n);

    for(int i=0; i<n; i++) cin>>a[i];

    int mx = *max_element(a.begin(), a.end()); //take max

    int x = mx-a[0];

    for(int i=1; i<n; i++) x = gcd(x, mx-a[i]); //getting most optimal value of x

    x = max(1LL, x); //maybe gcd is negative in some case which is only possible when there is no optimal value of x so we default to 1?

    sort(a.begin(), a.end());//sort it for binary search.

    int ans = 0;

    for(int i=0; i<n; i++) ans += (mx-a[i])/x; //operations to change a[i] to mx by adding x to it. Simple math.

    int k = -1;
    while(binary_search(a.begin(), a.end(), mx + x*k)) k--; //binary search till we don't find it.

    ans -= k; //k is negative so subtracting is same as addition of abs(k)

    cout<<ans<<'\n'; //voila! you got that!
}

 
//Main function
signed main()
{
    int tc = 1;
    cin>>tc;
    while(tc--) solve();
}