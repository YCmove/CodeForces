// https://blog.csdn.net/qq_42671946/article/details/86307373

#include "bits/stdc++.h"
using namespace std;
const long long inf = 2e9;
const int mod = 998244353 ;
long long  fac[1000004];
long long qk(long long a,long long n)
{
    long long ans=1;
    while (n)
    {
        if(n&1)ans=ans*a%mod;
        n>>=1;
        a=a*a%mod;
    }
    return ans;
}
int main()
{
    int n;
    while(cin>>n){
        fac[1]=1;
        for (int i = 2; i <= n; ++i) {
            fac[i]=fac[i-1]*i%mod;
        }
        long long ans=fac[n];
        for (int i = 1; i <= n-2; ++i) {
            ans=(ans  +  fac[n]  *  qk(fac[n-i],mod-2)  %  mod  *  (fac[n-i]-1)  %mod  )%mod;
        }
        printf("%lld\n",ans);
    }
 
}