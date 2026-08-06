#include <bits/stdc++.h>
using namespace std;
#define int long long

struct Cost
{
    multiset<int> low, high;
    int sumlow = 0, sumhigh = 0;

    /*
    Here we use the invariant with two multisets that is low.size() == high.size() + 1 or low.size() == high.size().
    Now the last element of low is median. Now the cost is minimised when we try to bring all elments to median so cost is summation of m - low where m is median and 
    summation of high - m. And hence we find the answer. The other method failed in various places because of tricky iterator updates. In that case we use only one multiset but its not worth the headache. Instead this method is clearer and is less prone to errors and all.
    */
    void balance()
    {
        while(low.size() > high.size() + 1)
        {
            auto it = prev(low.end());
            high.insert(*it);

            sumlow -= *it;
            sumhigh += *it;

            low.erase(it);
        }

        while(low.size() < high.size())
        {
            auto it  = high.begin();
            low.insert(*it);

            sumlow += *it;
            sumhigh -= *it;

            high.erase(it);
        }
    }

    void insert(int val)
    {
        if(low.empty() || val<=*low.rbegin())
        {
            low.insert(val);
            sumlow += val;
        }
        else
        {
            high.insert(val);
            sumhigh += val;
        }

        balance();
    }

    void del(int val)
    {
        if(low.find(val) != low.end())
        {
            low.erase(low.find(val));
            sumlow -= val;
        }
        else
        {
            high.erase(high.find(val));
            sumhigh -= val;
        }

        balance();
    }

    int cost()
    {
        int m = *low.rbegin();

        return m*low.size() + sumhigh - sumlow - m*high.size();
    }
};


void solve()
{
    int n,k; cin>>n>>k;
    vector<int> a(n);
    for(int i=0; i<n;i++) cin>>a[i];

    //special datatype to calculate cost for a window is created. Insert and delete are o(logn) even in worst case :)
    Cost c;

    for(int i=0; i<k; i++)
    {
        c.insert(a[i]);
    }

    cout<<c.cost()<<' ';

    for(int i=k; i<n; i++)
    {
        c.del(a[i-k]);
        c.insert(a[i]);

        cout<<c.cost()<<' ';
    }
}

signed main()
{
    int tc = 1;
    // cin>>tc;
    while(tc--) solve();
}