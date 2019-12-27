#include <bits/stdc++.h>
//#define int long long
using namespace std;
const int inf = 0x3f3f3f3f;
const int N = 2e4 + 10, M = 1e6 + 10;
int n, m, s, t, g, h[N], v[N], val[N], a[N], res;
int head[N], nex[M], to[M], w[M], tot = 1;
inline void ade(int a, int b, int c) {
    to[++tot] = b;
    nex[tot] = head[a];
    w[tot] = c;
    head[a] = tot;
}
inline void add(int a, int b, int c) {
    ade(a, b, c);
    ade(b, a, 0);
}
inline int bfs() {
    queue<int> q;
    q.push(s);
    memset(h, 0, sizeof h);
    h[s] = 1;
    while (q.size()) {
        int u = q.front();
        q.pop();
        for (int i = head[u]; i; i = nex[i]) {
            if (w[i] && !h[to[i]]) {
                h[to[i]] = h[u] + 1;
                q.push(to[i]);
            }
        }
    }
    return h[t];
}
int dfs(int x, int f) {
    if (x == t) return f;
    int fl = 0;
    for (int i = head[x]; i && f; i = nex[i]) {
        if (w[i] && h[to[i]] == h[x] + 1) {
            int mi = dfs(to[i], min(w[i], f));
            w[i] -= mi;
            w[i ^ 1] += mi;
            fl += mi;
            f -= mi;
        }
    }
    if (!fl) h[x] = -1;
    return fl;
}
inline int dinic() {
    int res = 0;
    while (bfs())
        res += dfs(s, inf);
    return res;
}
signed main() {
    cin >> n >> m >> g;
    t = n + m + 1;
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &v[i]);
        if (a[i])
            add(i, t, v[i]);
        else
            add(s, i, v[i]);
    }
    for (int i = 1, flag, k, x, num, p; i <= m; i++) {
        scanf("%d %d %d", &flag, &k, &num);
        while (num--) {
            scanf("%d", &x);
            if (flag)
                add(x, i + n, inf);
            else
                add(i + n, x, inf);
        }
        scanf("%d", &p);
        if (flag)
            add(n + i, t, k + p * g);
        else
            add(s, n + i, k + p * g);
        res += k;
    }
    cout << res - dinic() << endl;
    return 0;
}