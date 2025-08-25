//The euler project 3rd question to find the largest prime factor of 600851475143

#include<bits/stdc++.h>
using namespace std;
#define int long long

void solve()
{
    int n = 600851475143;
    int check = sqrt(n);
    vector<bool> isprime(check+1, true);
    isprime[0] = false, isprime[1] = false;
    vector<int> primes;

    //pre-computing primes Using seive of estrathos
    for(int i=2; i<check; i++)
    {
        if(isprime[i])
        {
            primes.push_back(i);
            for(int j=2*i; j<check; j+=i) 
            {
                isprime[j] = false;
            }
        }
    }

    int ans = 0;
    
    //Getting the answer
    for(int i=0; i<primes.size(); i++)
    {
        while(n%primes[i]==0) n/=primes[i];
        if(n==1)
        {
            ans = primes[i];
            break;
        }
    }

    if(n!=1) ans = n;

    cout<<ans<<endl;

    //CONCLUSION: Interesting concept of seive of estrathos. I like the idea of removing factors of a number and only storing till we want the primes.

}
 
signed main()
{
	int t=1;
	//cin >> t;
	while(t--){
	    solve();
	}
}