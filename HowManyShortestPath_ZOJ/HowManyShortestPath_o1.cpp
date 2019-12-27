#include <cstdio>
#include <cstring>
#include <queue>
#define MAXN 103
#define INF 0x3f3f3f3f
using namespace std;
int n, s, t;
int d[MAXN], map[MAXN][MAXN];
bool vis[MAXN];

void spfa(int st) {
    // init
    for (int i = 0; i < n; i++) {
        i == st ? d[i] = 0 : d[i] = INF;
        vis[i] = 0; // 0 is false
    }

    // BFS
    queue<int> q;
    q.push(st);
    vis[st] = 1; // true

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        vis[u] = 0; // false

        for (int v = 0; v < n; v++) {
            if (u == v || map[u][v] == -1) continue; // 略過同一點 和 兩點不相連
            int tmp = d[v];
            if (d[v] > d[u] + map[u][v]){
                d[v] = d[u] + map[u][v];
            }
            if (d[v] < tmp && !vis[v]){
                q.push(v);
                vis[v] = 1;
            }
        }
    }
}

struct Edge {
    int u, v, c, f;
};
struct Dinic {
    vector<Edge> E;
    vector<int> G[MAXN];
    bool vis[MAXN]; //BFS使用
    int lev[MAXN];  //记录层次
    int cur[MAXN];  //当前弧下标

    void init(int n) {
        E.clear();
        for (int i = 0; i < n; i++)
            G[i].clear();
    }

    void addedge(int from, int to, int cap) {
        E.push_back((Edge){from, to, cap, 0});
        E.push_back((Edge){to, from, 0, 0});
        int m = E.size();
        G[from].push_back(m - 2);
        G[to].push_back(m - 1);
    }
    bool bfs() {
        memset(vis, 0, sizeof(vis));
        queue<int> q;
        q.push(s);
        lev[s] = 0;
        vis[s] = 1; // true

        while (!q.empty()) {
            int now = q.front();
            q.pop();
            for (int i = 0; i < G[now].size(); i++) {
                Edge edge = E[G[now][i]];
                int nex = edge.v; // (u, v): v 是後面那點
                if (!vis[nex] && edge.c > edge.f) //属于残存网络的边
                {
                    lev[nex] = lev[now] + 1;
                    q.push(nex);
                    vis[nex] = 1;
                }
            }
        }
        return vis[t];
    }
    int dfs(int now, int aug) //now表示当前结点，aug表示目前为止的最小残量
    {
        if (now == t || aug == 0) return aug; //aug等于0时及时退出，此时相当于断路了
        int flow = 0, f;

        for (int &i = cur[now]; i < G[now].size(); i++)
        //从上次考虑的弧开始，注意要使用引用，同时修改cur[now]
        {
            Edge &edge = E[G[now][i]];
            int nex = edge.v;
            if (lev[now] + 1 == lev[nex] && (f = dfs(nex, min(aug, edge.c - edge.f))) > 0) {
                edge.f += f;
                E[G[now][i] ^ 1].f -= f;
                flow += f;
                aug -= f;
                if (!aug) break; //aug等于0及时退出，当aug!=0,说明当前节点还存在另一个增广路分支
            }
        }
        return flow;
    }
    int maxflow() //主过程
    {
        int flow = 0;
        while (bfs()) //不停地用bfs构造分层网络，然后用dfs沿着阻塞流增广
        {
            memset(cur, 0, sizeof(cur));
            flow += dfs(s, INF);
        }
        return flow;
    }
} dinic;

int main() {
    while (scanf("%d", &n) != EOF) {
        // nxn matrix
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                scanf("%d", &map[i][j]);
            }
        }

        // 讀取 s and t
        scanf("%d%d", &s, &t);
        if (s == t) {
            printf("inf\n");
            continue;
        }
        spfa(s);
        dinic.init(n);


        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                if (i != j && map[i][j] != -1 && d[i] != INF && d[j] != INF && d[i] + map[i][j] == d[j]) {
                    dinic.addedge(i, j, 1);
                }
            }
        }
        printf("%d\n", dinic.maxflow());
    }
}