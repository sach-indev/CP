//Includes
#include <bits/stdc++.h>
using namespace std;
 
//Macros
#define int long long
 
//global scope
const int inf = 1e18;
vector<int> a;
vector<array<int, 3>> op;   

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
    Can be solved o(n**2). So Here we just try to find first of all the record of all the segments. Now this can be done in O(n**2) as we know the fact that a good segmenet is one where:
    -> all elements are unique.
    -> max - min = r - l i.e difference between max and min is equal to the length of segment - 1. Here due to zero based indexing its equal to r-l.

    Now we use these facts to store good[mn][mx] = 1 if we meet the conditions.

    Next now see if we have a segment of size x and intial element as i than the good segment will have i as minimum element and i + x - 1 as maximum element in one of the segment and for other segment i+x will be min and i+2*x - 1 wil be max. As we have stored all the segments in good[min][max] so we can for each possible value of x and each starting element i whether g[i][i+x-1]==1 and g[i+x][i+2*x-1]==1. So we iterate x from n to 0 and if we find these conditons satisfied, we simply print it. Else we try until we exit the loop in which case there is no good segmenets. So 0 is our answer than.
    */



    int n; cin>>n;
    vector<int> a(n);

    for(int i=0; i<n; i++) cin>>a[i], --a[i];

    vector<vector<int>> good(n, vector<int>(n));

    for(int i=0; i<n; i++)
    {
        set<int> s;

        for(int j=i; j<n; j++)
        {
            if(s.count(a[j])) break;
            s.insert(a[j]);

            if(*s.rbegin() - *s.begin() == j - i) good[*s.begin()][*s.rbegin()] = 1;
        }
    }

    for(int ans = n; ans>0; ans--)
    {
        for(int i=0; i+2*ans-1<n; i++)
        {
            if(good[i][i+ans-1] && good[i+ans][i+2*ans-1]) return void(cout<<ans<<'\n');
        }
    }

    cout<<0<<'\n';
}

 
//Main function
signed main()
{
    int tc = 1;
    cin>>tc;
    while(tc--) solve();
}