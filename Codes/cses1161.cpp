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
    In this problem instead of seeing it as dividing the stick, see it as if you are merging all the sticks into one stick. Now as we can see if we merge two big sticks than cost is the total sum of the length of these sticks. Now this cost is high when we take larger sticks first as we have to than enventually merge these larger sticks with other sticks. So there cost is repeated.

    Now to minimize this what we do is we merge the smallest 2 sticks. Than we get a new stick of length = sum of length of two sticks. Now we simply find the next two smallest sticks and merge them. Continue this until we only have one stick left and at each point add the cost to the answer. This is huffman greedy used in huffman code. To simulate it we can use min heap.
    */
    int x, n; cin>>x>>n;
    priority_queue<int, vector<int>, greater<int>> pq;
    for(int i=0; i<n; i++)
    {
        int t; cin>>t;
        pq.push(t);
    }

    int cost = 0;
    while(pq.size() != 1)
    {
        int a = pq.top();
        pq.pop();
        int b = pq.top();
        pq.pop();

        cost += a+b;
        pq.push(a+b);
    }

    cout<<cost<<'\n';
}

 
//Main function
signed main()
{
    int tc = 1;
    // cin>>tc;  
    while(tc--) solve();
}