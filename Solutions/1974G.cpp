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
    So basically the greddy idea here is that if you are in some a[i] than you take the minimum from the months after u so that u minimize the cost and thus maximize the number of things u can take. Now u can do it by segment tree to store range queries and thus calculate but there's a clever trick here.
    
    The trick is to start from first index and always take if you can take and store the choices in a max heap. Now if you can't take than u see if the heap is empty or not and u compare ur maximum choice with the guy u can't take. So if ur max choice is larger than the guy u can't take than u take this guy and discard ur max choice. u also update ur budget which obviously increases now. This allows u take more people in the future. This works because u are optimizing ur choices on the fly and if u get any smaller guy u can't take, u take it in favour of ur largest guy and at last u are left with the smallest guys that u can take. 
    */
    int n, x; cin>>n>>x;
    vector<int> a(n);

    for(int i=0; i<n; i++) cin>>a[i];

    priority_queue<int> p;
    int s = 0;

    for(int i=0; i<n; i++)
    {
        if(s>=a[i])
        {
            s = s - a[i];
            p.push(a[i]);
        }

        else if(!p.empty())
        {
            if(p.top() > a[i])
            {
                s = s + p.top() - a[i];
                p.pop();
                p.push(a[i]);
            }
        }

        s += x;
    }

    cout<<p.size()<<'\n';
}

 
//Main function
signed main()
{

    int tc = 1;
    cin>>tc;
    while(tc--) solve();
}