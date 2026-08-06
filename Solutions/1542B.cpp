    #include<bits/stdc++.h>
    using namespace std;
    #define int long long

    void solve()
    {
        int n, a, b; cin>>n>>a>>b;

        if(a==1 || b==1)
        {
            if(a==1)
            {
                if((n-1)%b==0) cout<<"YES\n";
                else cout<<"NO\n";
                return;
            }

            if(b==1)
            {
                cout<<"YES\n";
                return;
            }
        }

        // while(n>1)
        // {
        //     if(n%a==0)
        //     {
        //         while(n%a && n>1) n = n/a;
        //     }

        //     else n = n - b;
        // }

        // if(n==1) cout<<"YES\n";
        // else cout<<"NO\n";

        //time limit exceeded even though worst case is o(n). What can I do better?

        int x = 1;
        bool ans = false;
        while(x<=n)
        {
            if((n-x)%b==0)
            {
                ans = true;
                break;
            }
            if(x>n/a) break;
            x = x*a;
        }

        if(ans) cout<<"YES\n";
        else cout<<"NO\n";

        //minor mistakes in seeing how it works. My point of view was correct but implementations suffered a bit. 

    }

    signed main()
    {
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        int t=1;
        cin >> t;

        while(t--)
        {
            solve();
        }
    }