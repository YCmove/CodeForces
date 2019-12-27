#include<cstdio>
#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
#define INF 0x3f3f3f3f
#define MAXN 2*(30011+1000)

using namespace std; 
int n,m;

struct Edge{
    int u,v,c,f;
};

struct Dinic
{
    int s,t;
    vector<Edge> E;
    // MAXN 2*(30011+1000)
    vector<int> G[MAXN]; // G[x][y] 代表X點連接的邊
    bool vis[MAXN]; // bfs使用
    int lev[MAXN]; // bfs時設定
    int cur[MAXN];

    void init(int n) 
    {
        E.clear();
        for(int i=0;i<=n;i++) G[i].clear();
    }

    void addedge(int from,int to,int cap)
    {
        //                 u,   v,  c, f
        E.push_back((Edge){from,to,cap,0});
        E.push_back((Edge){to,from,0,0}); // 連接反邊(Residual Graph)
        G[from].push_back(E.size()-2); // G對應到E的Edge, 正邊
        G[to].push_back(E.size()-1); // 反邊
    }

    bool bfs()
    {
        memset(vis,0,sizeof(vis));
        queue<int> q;
        q.push(s);
        lev[s]=0; // soure level = 0
        vis[s]=1; // vis 代表 1, 已拜訪

        while(!q.empty())
        {
            int now=q.front(); q.pop();
            for(int i=0;i<G[now].size();i++)
            {
                Edge edge=E[G[now][i]];
                int nex=edge.v;
                if(!vis[nex] && edge.c>edge.f)
                {
                    lev[nex]=lev[now]+1; // 建立level graph
                    q.push(nex);
                    vis[nex]=1;
                }
            }
        }
        return vis[t]; // 只有走到終點才會回傳True
    }


    int dfs(int now,int aug) // 要做augmenting
    {
        if(now==t || aug==0) return aug; 99++ // ??

        int flow=0,f;

        for(int& i=cur[now];i<G[now].size();i++)
        {
            Edge& edge=E[G[now][i]];
            int nex=edge.v;
            // dfs 往深處走，直到flow大於0
            if(lev[now]+1 == lev[nex] && (f=dfs(nex, min(aug, edge.c-edge.f)))>0)
            {
                edge.f+=f; // 反邊增加流量
                E[G[now][i]^1].f-=f; // 正邊減少流量 XOR
                // 偶数^1 加一   奇数^1 减一  因此 2和3 4和5都为一对正反边
                flow+=f;
                aug-=f;
                if(!aug) break;
            }
        }
        return flow;
    }
    int maxflow()
    {
        int flow=0;
        while(bfs())
        {
            memset(cur,0,sizeof(cur));
            flow+=dfs(s,INF);
        }
        return flow;
    }
}dinic;

int in(int x){return x;}
int out(int x){return x+n;}

int main()
{
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&m);//n个点，m条边
        dinic.init(2*n+2);
        for(int i=1;i<=m;i++)
        {
            int from,to;
            scanf("%d%d",&from,&to);
            if(1<=from && from<=n && 1<=to && to<=n)
            {
                dinic.addedge(out(from),in(to),1);
                dinic.addedge(out(to),in(from),1);
            }
        }
        dinic.s=0, dinic.t=2*n+2;

        dinic.addedge(dinic.s,in(2),2); 
        dinic.addedge(out(1),dinic.t,1);
        dinic.addedge(out(3),dinic.t,1);

        for(int i=1;i<=n;i++) dinic.addedge(in(i),out(i),i==2?2:1);
        
        if(dinic.maxflow()==2) printf("YES\n");
        else printf("NO\n");
    }
}