// https://www.itread01.com/content/1519653483.html
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
#define ll long long
#define maxn 300005

using namespace std;

int ans=0,g[maxn];
int n,m,id[maxn],u,v;
int f[maxn],hd[maxn];
int to[maxn],ne[maxn];
bool vis[maxn];
char s[maxn];

inline int num(char x){
	return x - 'a';
}

inline bool topsort(){
	queue<int> q;
	int x,tot=0;
	
	for(int i=1;i<=n;i++) if(!id[i]) q.push(i);
	
	while(!q.empty()){
		x=q.front(),q.pop(),tot++;
		for(int i=hd[x];i;i=ne[i]) if(!(--id[to[i]]))
		    q.push(to[i]);
	}
	
	return tot==n;
}


int dp(int x){
	if(vis[x]) return g[x];
	vis[x]=1,g[x]=0;
	for(int i=hd[x];i;i=ne[i]) g[x]=max(g[x],dp(to[i]));
	g[x]+=f[x];
	return g[x];
}

int main(){
	scanf("%d%d",&n,&m);
	scanf("%s",s+1);
	for(int i=1;i<=m;i++){
		scanf("%d%d",&u,&v);
		to[i]=v,ne[i]=hd[u];
		hd[u]=i,id[v]++;
	}
	
	if(!topsort()){
		puts("-1");
		return 0;
	}
	
	for(int i=0;i<26;i++){
		memset(vis,0,sizeof(vis));
		for(int j=1;j<=n;j++) f[j]=(num(s[j])==i);
		
		for(int j=1;j<=n;j++) ans=max(ans,dp(j));
	}
	
	printf("%d\n",ans);
	return 0;
	
}