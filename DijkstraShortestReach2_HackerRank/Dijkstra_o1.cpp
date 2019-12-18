#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<vector<pair<int, int>>> graph;
int min_cost[3003];

struct node {
    int i, k;
    bool operator<(const node &x) const {
        return k > x.k;
    }
};

void dijk(int S) {
    memset(min_cost, 63, sizeof(min_cost));
    priority_queue<node> Q;
    Q.push({S, 0});
    min_cost[S] = 0;
    while (Q.size()) {
        int cur_node = Q.top().i;
        int cost = Q.top().k;
        Q.pop();
        for (int i = 0; i < graph[cur_node].size(); i++) {
            int child = graph[cur_node][i].first;
            int cost2 = graph[cur_node][i].second;
            if (min_cost[child] > cost + cost2) {
                min_cost[child] = cost + cost2;
                Q.push({child, min_cost[child]});
            }
        }
    }
}

int main(void) {
    int t, n, m;
    int x, y, r;
    int S;
    cin >> t;
    while (t--) {
        cin >> n >> m;
        graph = vector<vector<pair<int, int>>>(n + 1);
        for (int i = 0; i < m; i++) {
            cin >> x >> y >> r;
            graph[x].push_back(make_pair(y, r));
            graph[y].push_back(make_pair(x, r));
        }
        cin >> S;
        dijk(S);
        for (int i = 1; i <= n; i++) {
            if (i != S) {
                cout << (min_cost[i] == min_cost[0] ? -1 : min_cost[i]) << " ";
            }
        }
        cout << endl;
    }
}