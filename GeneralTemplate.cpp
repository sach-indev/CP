#include<bits/stdc++.h>
using namespace std;
#define int long long
 
int fact5(int a)
{
    int cnt = 0;
    while(a%5==0)
    {
        cnt++;
        a/=5;
    }

    return cnt;
}

void solve()
{
    //your code
}
 
signed main()
{
	int t=1;
	//cin >> t;
	while(t--){
	    solve();
	}
}