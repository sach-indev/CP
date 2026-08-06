//Includes
#include <bits/stdc++.h>
using namespace std;
 
//Macros
#define int long long
 
//global scope
const int inf = 1e18;
static const int mod = 1e9 + 7;

//classes
class matrix
{
    public: 
    int n, m;
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
    The core idea is to divide the string into minsize segments which contains all the k alphabets. If number of such segments are greater than or equal to n than we can get all the subsequnces of size n with k alphabets. Else we can always pick the last character from each block and than pick any character not in the last block (which is gurranted to not have all k alphabets if it exists). Than such a subsequnce is impossible to make.
    
    Ok so first take a string aabbccabab Now let n and k be 3. Now see if we can  divide this string into blocks of minimum sizes such that each block has at least one occurence of k alphabet. After making all such blocks, we will add the reamining characters in last block which is gurranted to be either empty or with some of the first alphabets with at least 1 missing. Now after dividing the string we have the following blocks. 
    
    aabbc cab ab

    Now as we see there are only two blocks so we can't make all the subsequnces of size n containg k alphabets. Now to create one such string that is not present as subsequence in this string, take the last character from each block. So now our string is: 
    
    cb

    So now in the last block c is not there so to make our string's size 3 we add c to it. So now

    cbc 

    is our final answer string. Note that when you try to make cbc you have to pick last element of first block as you can't pick from behind it. And thus you can't make cbc as you are gurranted to not be able to find c in the last block. 
    */

    int n, k, m; cin>>n>>k>>m;
    string a, t = ""; cin>>a;

    set<char> s;

    for(int i=0; i<m; i++)
    {
        s.insert(a[i]);

        if(s.size()==k)
        {
            s.clear();
            t += a[i];
        }
    }

    if(t.size() < n)
    {
        cout<<"NO\n";
        char c = 'a';

        while(s.count(c)) c++;

        while(t.size()<n) t.push_back(c);

        cout<<t<<'\n';
    }
    else cout<<"YES\n";
}

 
//Main function
signed main()
{

    int tc = 1;
    cin>>tc;
    while(tc--) solve();
}