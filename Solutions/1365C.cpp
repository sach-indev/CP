#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    //WA in test case 5. We just match first element and pray that it works. 
    // int check = a[0];
    // int rotate = -1;
    // for(int i=0; i<n; i++)
    // {
    //     if(check == b[i])
    //     {
    //         rotate = i;
    //         break;
    //     }
    // }
    // int ans = 0;
    // for(int i=0; i<n; i++)
    // {
    //     if(a[i]==b[(i+rotate)%n]) ans++;
    // }


    // TLE on test case 7. Can we do better?
    // int ans = LLONG_MIN;
    // for(int i=0; i<n; i++)
    // {
    //     int temp = 0;
    //     for(int j=0; j<n; j++)
    //     {
    //         if(a[j]==b[(j+i)%n]) temp++;
    //     }
    //     ans = max(ans, temp);
    // }

    //So the solution was something like this. So we know that for every a[i]=b[j] the shift is unique as a and b are permuntation of n. Now we just have to count which type fo shift (like if we do 2 shift, 3 shift etc) makes the most elements equal. I was thinking of finding j for each a[i] such that b[j]==a[i] by for(for loop) but we can just do hashing! So the take away is to do hashing to store positions of a[i] and than store the frequencies of j-i or n+j-i(if j -i<0). Than find the max of these frequencies. Time complexity : O(nlogn) as we are using map.

    int n; cin>>n;
    vector<int> a(n), b(n), pos(n+1);
    map<int, int> shifts;
    for(int i=0; i<n; i++) cin>>a[i];
    for(int i=0; i<n; i++) cin>>b[i];

    for(int i=0; i<n; i++) pos[a[i]] = i;

    for(int i=0; i<n; i++)
    {
        int cur = pos[b[i]] - i;
        if(cur<0) cur += n;

        shifts[cur]++;
    }

    int ans = 0;
    for(const auto &i: shifts)
    {
        ans = max(ans, i.second);
    }

    cout<<ans<<'\n';


}
  
signed main()
{
	ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t=1;
	// cin>>t;
    while(t--)
    {
        solve();
    }
}

//conclusion: Consider hashing and avoid for(for loops).