// https://blog.csdn.net/qq_29480875/article/details/60151302
//  main.cpp
//  C. Mahmoud and a Message
//
//  Created by teddywang on 2017/2/8.
//  Copyright © 2017年 teddywang. All rights reserved.
//
 
#include <iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
char s[10000];
int t[10000];
int name[27];
int dp[10001];
int pre[10000];
int n;
const int mod=1e9+7;
int er[1002];
void n2()
{
    er[1]=1;
    for(int i=2;i<=1001;i++)
        er[i]=(er[i-1]*2)%mod;
}
 int getnum( int a)
{
    if(n-a<=pre[a]) return er[n-a];
    int ans=0;
    for(int i=0;i<pre[a];i++)
    {
        ans+=(getnum(a+i+1))%mod;
        ans%=mod;
    }
    return ans;
}
int main()
{
    n2();
    while(~scanf("%d",&n))
    {
        scanf("%s",s);
        for(int i=0;i<26;i++)
            scanf("%d",&name[i]);
        for(int i=0;i<n;i++)
            t[i]=name[s[i]-'a'];
        memset(pre,0,sizeof(pre));
        memset(dp,0,sizeof(dp));
        int ans2=0;
        for(int i=0;i<n;i++)
        {
            int mins=t[i];
            for(int j=0;i+j<n;j++)
            {
                mins=min(mins,t[i+j]);
                if(mins>=j+1) pre[i]++;
                else break;
            }
            ans2=max(ans2,pre[i]);
        }
        int ans1=0;
        dp[n-1]=1;
        for(int i=n-2;i>=0;i--)
        {
            if(n-i<=pre[i]) dp[i]=er[n-i];
            else for(int j=0;j<pre[i];j++)
            {
                dp[i]=(dp[i]+dp[i+j+1])%mod;
            }
        }
        ans1=dp[0];
        cout<<ans1%mod<<endl;
        cout<<ans2<<endl;
        int ans3=0;
        for(int i=0;i<n;)
        {
            ans3++;
            i+=pre[i];
        }
        cout<<ans3<<endl;
    }
}