        #include <bits/stdc++.h>
        #include <bit>
        using namespace std;
        #define int long long

        // global variables
        const static int mod = 998244353;
        const static int maxn = 20;
        //  vector<int> fact(maxn+1, 1);
        //  vector<int> seive(maxn + 1, 1);
        //  vector<int> primes;
        // functions and clases

        int binpow(int a, int exp)
        {
            if(exp==0) return 1;
            int res = 1;
            while(exp > 0)
            {
                if(exp&1) res = (res*a)%mod;
                a = (a*a)%mod;
                exp >>= 1;
            }

            return res%mod;
        }

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

        int popcount(int n)
        {
            return __builtin_popcountll(n);
        }

        int bitsize(int n)
        {
            if(n==0) return 0;
            else return 64 - __builtin_clzll(n);
        }

        void solve()
        {

            /*
            In this problem, the goal was to find the pairs x, y such that all given m pairs have x or y in them. Here instead of checking all the pairs we could have done something like this:

            Let the first of the m pairs be a1, b1. Now we know that one of them is x or y. Now let us make cases. 
            
            a1 case: Suppose a1 is the one which is one of x or y. Now we just find from the rest of the m-1 pairs whether there is a pair that does not contain a1. 
            ->If we could not find such pair that means a1 is in every pair and so we can have any number as y. So we can have n-1 pairs for a1.
            ->If we could find such pairs u,v than now we can say that we can have the pairs as a1, u and a1, v. These are the only possible pairs that we can have with a1. Why? Because any other we found with a1, let it be a1, c. Now u,v is a pair and are both not equal to a1, c. So we can't have any other pairing with c expect u and v. Now we just check whether all m pairs satisfy these u and v and we are done!

            b1 case: Very similar to a1 case. Basically just repeat.

            Now there is one bug that I encountered in this approach. It is imperative to discuss it here.

            First of all if both a1 and b1 are in every pair than we will double count x, y pair so that's why we have to decrement. 

            Second if even one of the a1 or b1 is in every pair than we may insert count x,y twice. We can check this by storing these pairs in a set and deleting x,y if it exists here as it will be the only ovrelapping pair.

            
            */

            


            int n, m; cin>>n>>m;
            vector<pair<int, int>> a(m);

            for(int i=0; i<m; i++)
            {
                cin>>a[i].first>>a[i].second;
            }

            int x = a[0].first, y = a[0].second;
            pair<int, int> xp = {-1, -1}, yp = {-1, -1};

            for(int i=1; i<m; i++)
            {
                if(a[i].first!=x && a[i].second!=x)
                {
                    xp.first = a[i].first;
                    xp.second = a[i].second;
                    break;
                }
            }

            for(int i=1; i<m; i++)
            {
                if(a[i].first!=y && a[i].second!=y)
                {
                    yp.first = a[i].first;
                    yp.second = a[i].second;
                    break;
                }
            }

            // cout<<'\n'<<x<<','<<y<<'\n';
            // cout<<endl;
            // cout<<xp.first<<','<<xp.second<<'\n'<<yp.first<<','<<yp.second<<'\n';
            // cout<<endl;

            set<pair<int, int>> s;

            int ans = 0LL;
            if(xp.first==-1)
            {
                ans += n-1;
            }
            else
            {
                bool check = true;
                for(int i=0; i<m; i++)
                {
                    if(a[i].first!=x && a[i].first!=xp.first && a[i].second!=x && a[i].second!=xp.first)
                    {
                        check = false;
                        break;
                    }
                }

                if(check)
                {
                    s.insert(make_pair(min(x, xp.first), max(x, xp.first)));
                }
                check = true;
                for(int i=0; i<m; i++)
                {
                    if(a[i].first!=x && a[i].first!=xp.second && a[i].second!=x && a[i].second!=xp.second)
                    {
                        check = false;
                        break;
                    }
                }

                if(check)
                {
                    s.insert(make_pair(min(x, xp.second), max(x, xp.second)));
                }
            }

            if(yp.first==-1)
            {
                ans += n-1;
                if(xp.first==-1) ans--;
            }
            else
            {
                bool check = true;
                for(int i=0; i<m; i++)
                {
                    if(a[i].first!=y && a[i].first!=yp.first && a[i].second!=y && a[i].second!=yp.first)
                    {
                        check = false;
                        break;
                    }
                }

                if(check)
                {
                    s.insert(make_pair(min(y, yp.first), max(y, yp.first)));
                }
                check = true;
                for(int i=0; i<m; i++)
                {
                    if(a[i].first!=y && a[i].first!=yp.second && a[i].second!=y && a[i].second!=yp.second)
                    {
                        check = false;
                        break;
                    }
                }

                if(check)
                {
                    s.insert(make_pair(min(y, yp.second), max(y, yp.second)));
                }
            }

            // for(auto [a, b] :  s)
            // {
            //     cout<<a<<','<<b<<'\n';
            // }

            if(xp.first==-1 || yp.first==-1)
            {
                s.erase(make_pair(min(x, y), max(x, y)));
            }
            cout<<ans + s.size()<<'\n';
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
            // cin>>tc;
            while (tc--)
                solve();
        }