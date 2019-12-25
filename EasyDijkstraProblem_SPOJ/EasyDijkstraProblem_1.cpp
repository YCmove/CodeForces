// 重要基本概念
#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int > PI;
#define first ff;
#define second ss;

const int MAXN = 1e4+1;
const int MAXW = 1e9+1;
int n, m;

bool vis[MAXN];
int cost[MAXN];
vector<vector<PI> > g; // neighbor and dist
priority_queue<PI > q; // cost and node


void dijkstra(int src){
    // PI node = g[src];
    q.push(make_pair(0, src));

    if (vis[src])continue;
    vis[src] = true;

    while(!q.empty()){


    }

}



int main(){
    int test_n;
    cin >> test_n;

    while(--test_n){
        cin >> n >> m;
        // Initial
        g.clear();
        g.resize(n);
        while(!q.empty()) q.pop();
        for (int i; i<n; ++i) cost[i] = MAXW, vis[i]=false;



        for (int i = 0; i<m; ++i){
            int a, b, w;
            cin >> a >> b >> w;
            g[a].push_back(make_pair(b, w));
        }


        // query
        int x, y;
        dijkstra(x);

        cin >> x >> y;
        if (cost == MAXW) {
            cout << "NO" << '\n';
        } esle {
            cout << cost[y] << '\n';
        }

    }
    return 0;
}