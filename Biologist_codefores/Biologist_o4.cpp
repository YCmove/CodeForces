#include <bits/stdc++.h>

using namespace std;

#define dbg(x...) do { cout << #x << " -> "; err(x); } while (0)

void err() { cout << endl; }

template<class T, class... Ts>
void err(const T &arg, const Ts &... args) {
    cout << arg << ' ';
    err(args...);
}

#define endl "\n"
using ll = long long;
using db = double;

const int INF = 0x3f3f3f3f;
const int N = 1e5 + 10;

struct Dinic {
    static const int M = 2e6 + 10;
    static const int N = 1e5 + 10;

    struct Edge {
        int to, nxt;
        int flow;

        Edge() {}

        Edge(int to, int nxt, int flow) : to(to), nxt(nxt), flow(flow) {}
    } edge[M];

    int S, T;
    int head[N], tot;
    int dep[N];

    void init() {
        memset(head, -1, sizeof head);
        tot = 0;
    }

    void set(int _S, int _T) {
        S = _S;
        T = _T;
    }

    void addedge(int u, int v, int w, int rw = 0) {
        edge[tot] = Edge(v, head[u], w);
        head[u] = tot++;
        edge[tot] = Edge(u, head[v], rw);
        head[v] = tot++;
    }

    bool BFS() {
        memset(dep, -1, sizeof dep);
        queue<int> q;
        q.push(S);
        dep[S] = 1;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int i = head[u]; ~i; i = edge[i].nxt) {
                if (edge[i].flow && dep[edge[i].to] == -1) {
                    dep[edge[i].to] = dep[u] + 1;
                    q.push(edge[i].to);
                }
            }
        }
        return dep[T] >= 0;
    }

    int DFS(int u, int f) {
        if (u == T || f == 0) return f;
        int w, used = 0;
        for (int i = head[u]; ~i; i = edge[i].nxt) {
            if (edge[i].flow && dep[edge[i].to] == dep[u] + 1) {
                w = DFS(edge[i].to, min(f - used, edge[i].flow));
                edge[i].flow -= w;
                edge[i ^ 1].flow += w;
                used += w;
                if (used == f) return f;
            }
        }
        if (!used) dep[u] = -1;
        return used;
    }

    int solve() {
        int ans = 0;
        while (BFS()) {
            ans += DFS(S, INF);
        }
        return ans;
    }
} dinic;

int n, m, g;
int a[N];

void RUN() {
    while (cin >> n >> m >> g) {
        dinic.init();
        int S = 0, T = n + m + 1;
        dinic.set(S, T);
        for (int i = 1; i <= n; ++i) {
            cin >> a[i];
        }
        for (int i = 1, v; i <= n; ++i) {
            cin >> v;
            if (a[i]) {
                dinic.addedge(i, T, v);
            } else {
                dinic.addedge(S, i, v);
            }
        }
        int sum = 0;
        for (int i = 1, folk, w, k, op; i <= m; ++i) {
            cin >> folk >> w >> k;
            sum += w;
            if (folk == 0) {
                for (int j = 1, x; j <= k; ++j) {
                    cin >> x;
                    dinic.addedge(n + i, x, INF);
                }
                cin >> op;
                dinic.addedge(S, n + i, w + g * op);
            } else {
                for (int j = 1, x; j <= k; ++j) {
                    cin >> x;
                    dinic.addedge(x, n + i, INF);
                }
                cin >> op;
                dinic.addedge(n + i, T, w + g * op);
            }
        }
        cout << sum - dinic.solve() << endl;
    }
}

int main() {
#ifdef LOCAL_JUDGE
    freopen("input.txt", "r", stdin);
#endif

    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    RUN();

#ifdef LOCAL_JUDGE
    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
#endif
    return 0;
}