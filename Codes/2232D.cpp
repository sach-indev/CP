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

void hanoi(int n, int s, int u, int d)
{
    if(n<=0) return;
    if(n==1)
    {
        op.push_back({n, s, d});
        return;
    }

    if(a[n]==0)
    {
        hanoi(n-1, s, d, u);

        op.push_back({n, s, d});

        hanoi(n-1, u, s, d);
    }

    else
    {
        hanoi(n-1-a[n], s, d, u);

        op.push_back({n, s, d});

        hanoi(n-1-a[n], u, d, s);
        hanoi(n-1, s, u , d);
    }
}



//Solution Per Test Case
void solve()
{
    /*
    If we consider that we have three tables a, b and c. Classic tower of hanoi is solved like this:

    take n-1 above and put them on b
    take n single disk and put it on c
    take n-1 above and put them on c

    Now this question is similar but catch is sometimes the n disk can only be moved if it has exactly a[n] disks above it. Now we can see that nth disk can have at most n-1 disks above it due to the property given to us. So now if a[n] >= n for any n in the array than the answer is simply not possible.

    Now if answer is possible i.e. for all n a[n] < n than we can do the following things.

    if a[n] = 0 than it becomes classic hanoi so 
    move n-1 to b
    move n to c
    move n-1 to c

    but if a[n] != 0 than we have to make it such that there are a[n] disks above n. Now total disks above n are n-1. So now we first move n-1-a[n] disks from top to b.

    move n-1-a[n] to b
    move n to c
    move n-1-a[n] to a
    move n-1 to c

    We just have to do recursion now to implement this....
    */

    int n; cin>>n; 
    a.resize(n+1);

    for(int i=1; i<=n; i++) cin>>a[i];

    for(int i=1; i<=n; i++)
    {
        if(a[i]>=i) return void(cout<<"NO\n");
    }

    cout<<"YES\n";

    hanoi(n, 1, 2, 3);

    cout<<op.size()<<"\n";

    for(auto p : op) cout<<p[0]<<' '<<p[1]<<' '<<p[2]<<'\n';
    op.clear();
}

 
//Main function
signed main()
{

    int tc = 1;
    cin>>tc;
    while(tc--) solve();
}