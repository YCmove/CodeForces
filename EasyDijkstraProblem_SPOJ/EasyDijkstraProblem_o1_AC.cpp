#include <stdio.h>
#include <vector>
#include <queue>
#include <memory.h>

using namespace std;

int const N = 1e4 + 1;
int const M = 1e9 + 1;
int n, m, cost[N];
bool vis[N];
vector<vector<pair<int, int> > > g; // pair 為 neighbor and weight
priority_queue<pair<int, int> > q; // pair 為 weight 和 node
// g, q, cost, vis 都需要初始化

void Dijkstra(int src) {
    int v, c;
    
    cost[src] = 0; // src 起始距離為0
    q.push(make_pair(0, src));
    
    while(!q.empty()) {
        v = q.top().second;
        c = -q.top().first; // 重要，cost越負代表cost越大
        q.pop();
        
        if(vis[v]) continue;
        vis[v] = true;
        
        for(int i = 0; i < g[v].size(); i++)
        {
            // g[v][i].second + c: 鄰居的weight加上目前node的weight，比較小的話就更新
            if(g[v][i].second + c < cost[g[v][i].first]) {
                cost[g[v][i].first] = g[v][i].second + c;
                q.push(make_pair(-(g[v][i].second + c), g[v][i].first));
            }
        }
    }
}

int main() {
    int t;
    scanf("%d", &t);
    
    while(t--) {
        scanf("%d%d", &n, &m);
        
        // init
        g.clear();
        g.resize(n); // vector<vector<pair<int, int>>>的初始化
        while(!q.empty()) q.pop(); // 清空queue
        for(int i = 0; i < n; i++) cost[i] = M; // cost 初始化到最大
        memset(vis, false, sizeof vis); // 初始化visited table to false
        
        int v, u, c;
        
        while(m--) {
            scanf("%d%d%d", &v, &u, &c);
            v--; u--;
            g[v].push_back(make_pair(u, c));
        }
        
        // query
        scanf("%d%d", &v, &u);
        v--; u--;
        
        Dijkstra(v);
        
        if(cost[u] == M) puts("NO"); // 距離最大代表兩點間沒有相連
        else printf("%d\n", cost[u]);
    }
    
    return 0;
}