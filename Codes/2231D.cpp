    #include <bits/stdc++.h>
    using namespace std;
    #define int long long

    //global variables
    // const static int mod = 1e18;
    // const static int maxn = 1e5*3; 
    // vector<int> fact(maxn+1, 1), seive(maxn + 1, 1);
    // vector<int> primes;
    //functions and clases

    // int binpow(int a, int exp)
    // {
    //     if(exp==0) return 1;
    //     int res = 1;
    //     while(exp > 0)
    //     {
    //         if(exp&1) res = (res*a)%mod;
    //         a = (a*a)%mod;
    //         exp >>= 1;
    //     }

    //     return res%mod;
    // }

    // int comb(int n, int k)
    // {
    //     int res = (fact[n]*binpow(fact[n-k], mod-2))%mod;
    //     res = (res*binpow(fact[k], mod-2))%mod;

    //     return res%mod;
    // }

    // class Aggstack
    // {
    //     public:
    //     stack<pair<int, int>> st;

    //     void push(int x)
    //     {
    //         int cur = (st.empty() ? x : max(x, st.top().second));
    //         st.push(make_pair(x, cur));
    //     }

    //     void pop()
    //     {
    //         st.pop();
    //     }

    //     bool empty()
    //     {
    //         return st.empty();
    //     }

    //     pair<int, int> top()
    //     {
    //         return st.top();
    //     }
    // };

    // class Aggqueue
    // {
    //     public:
    //     Aggstack in, out;

    //     void push(int x)
    //     {
    //         in.push(x);
    //     }

    //     void pop()
    //     {
    //         if(out.empty())
    //         {
    //             while(!in.empty())
    //             {
    //                 out.push(in.top().first);
    //                 in.pop();
    //             }
    //         }

    //         out.pop();
    //     }

    //     int op()
    //     {
    //         if(out.empty()) return in.top().second;
    //         if(in.empty()) return out.top().second;

    //         return max(in.top().second, out.top().second);
    //     }
    // };
    
    
    
    void solve()
    {

        /*
        In this problem we had two observations:
        wherever c[i] != c[i-1], there b[i] = c[i];
        why? suppose c is as x, x, x, y, z
        
        now by defination of c y>x and wherever there is a divide between x and y, b[i] has to be bigger than x for there to be change in the maximum becuase c[i] = max(c[i-1], b[i]). Hence in these places b[i] = c[i] i.e. b[i] can be determined.

        Now suppose in this same place s[i] == 1 i.e. we are also given a[i] for this position. So now we know
        b[i] = b[i-1] + a[i] and thus b[i-1] can also be determined so we determine it. Now we check whether samething happens for i-1 or not i.e s[i-1] == '1' or not. We do this until s[i-1] != '1'.

        After this we have determined the key points which are determinable. Now we build b from start as b[1] is always determinable. So now from i=2 to n we can have:

        s[i] == '1' in which case b[i] = b[i-1] + a[i];
        else if(d[i]==0) so this b[i] is not determinable so we give it the smallest value so it doesn't affect the value of c[i]. let if be -inf.


        After all this we have an completed b array. Now we just check for each inded i whether there is someone such that max(c[i-1], b[i]) != c[i]. If there is than the answer is no, otherwise we print b[i] - b[i-1] = a[i] as our main array as answer.
        */


        int n; cin>>n;
        vector<int> a(n+1), b(n+1, 0), c(n+1, -1e18), d(n+1, 0);
        string s; cin>>s; s = " " + s;d[0] = 1;

        for(int i=1; i<=n; i++) cin>>a[i];
        for(int i=1; i<=n; i++) cin>>c[i];

        for(int i=1; i<=n; i++)
        {
            if(c[i] != c[i-1])
            {
                if(c[i] < c[i-1]) return void(cout<<"NO\n");
                b[i] = c[i];
                d[i] = 1;

                for(int j=i; j>=0; j--)
                {
                    if(s[j]=='1')
                    {
                        if(d[j-1] && b[j-1] + a[j] != b[j]) return void(cout<<"NO\n");
                        d[j-1] = 1; b[j-1] = b[j] - a[j];
                    }
                    else break;
                }
            }
        }
        
        
        // cout<<endl<<endl;
        // for(int i=1; i<=n; i++) cout<<d[i]<<' ';
        // cout<<endl;
        // for(int i=1; i<=n; i++) cout<<b[i]<<' ';
        // cout<<endl;
        // for(int i=1; i<=n; i++) cout<<a[i]<<' ';
        // cout<<endl;
        for(int i=1; i<=n; i++)
        {
            if(s[i] == '1') b[i] = b[i-1] + a[i], d[i] = 1;
            if(!d[i]) b[i] = -1e16;
            a[i] = b[i] - b[i-1];
            if(max(c[i-1], b[i]) != c[i]) return void(cout<<"NO\n");
        }

        cout<<"YES\n";
        for(int i=1; i<=n; i++)
        {
            cout<<a[i]<<" \n"[i==n];
        }
    }

    signed main()
    {
        // for(int i=1; i<=maxn; i++) fact[i] = (fact[i-1]*i)%mod;
        // seive[0] = 0;
        // seive[1] = 0;
        // for(int i=0; i<=maxn; i++)
        // {
        //     if(seive[i])
        //     {
        //         for(int j=i*i; j<=maxn; j+=i)
        //         {
        //             seive[j] = 0;
        //         }
        //     }
        // }

        // for(int i=0; i<=maxn; i++)
        // {
        //     if(seive[i] == 1)
        //     {
        //         primes.push_back(i);
        //     }
        // }

        int tc = 1;
        cin>>tc;
        while(tc--) solve();
    }