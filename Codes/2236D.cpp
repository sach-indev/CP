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
    Here we have to make only one observation: 

    if we have two elements that are connceted that is say we have two unique elements x and y such that y-x <= k or if we choose k tha [x , x+k] contains y than we can always get ergo to win. 
    
    How? First if we have n such people in our range [x, x+k] than we take the last two elements ok. Now see if they are a and b say than suppose there are n a's and m b's.

    Now if m is even than we can choose b and ergo will win because [b, b+k] only has b as it is the last connected one. And as m is even so ergo will be the last to choose as after that there would be no moves.

    and if m is odd than we choose a and now ergo will choose b. As m is odd so last choice would be with ergo and thus again ergo wins.

    So if there are any connected guys we can make ergo win so answer is yes.

    Next if there are no connected guys than we check whether there are any element with odd frequency. If yes than we can choose this element and make ergo win. So if any odd frequency exists than ergo wins.

    Else there is no way for ergo to win at all. So we ouput No.
    
    */
    int n, k; cin>>n>>k;
    vector<int> a(n);

    map<int, int> mp;

    for(int i=0; i<n; i++)
    {
        cin>>a[i];
        mp[a[i]]++;
    }

    vector<int> p;
    for(auto [a, b] : mp) p.push_back(a);

    for(int i=1; i<p.size(); i++)
    {
        if(p[i]-p[i-1] <= k) return void(cout<<"YES\n");
    }

    for(auto [a, b] : mp)
    {
        if(!(b&1)) return void(cout<<"YES\n");
    }

    cout<<"NO\n";
}

 
//Main function
signed main()
{

    int tc = 1;
    cin>>tc;
    while(tc--) solve();
}