#include <bits/stdc++.h>
#define MX 1005
using namespace std;

vector<int> V[MX];
long long cap[MX][MX];
int padre[MX];
int n;

long long bfs(int s, int t) {
    fill(padre, padre + n + 1, -1); ///n
    padre[s] = s;
    queue<pair<int, long long>> cola; ///nodo, flujo
    cola.push({s, 1000000000});       ///infinito
    while (!cola.empty()) {
        int nodo = cola.front().first;
        long long f = cola.front().second;
        cola.pop();
        for (auto v : V[nodo]) {
            //cout << v << "," << padre[v] << "," << cap[nodo][v] << " ";
            if (padre[v] == -1 && cap[nodo][v]) {
                padre[v] = nodo;
                f = min(f, cap[nodo][v]);
                if (v == t) return f;
                cola.push({v, f});
            }
        }
    }
    return 0;
}

long long edmond(int s, int t) {
    long long f = 0, aumento = bfs(s, t);
    while (aumento) {
        f += aumento;
        int nodo = t;
        while (nodo != s) {
            int ant = padre[nodo];
            cap[ant][nodo] -= aumento;
            cap[nodo][ant] += aumento;
            nodo = ant;
        }
        aumento = bfs(s, t);
    }
    return f;
}

int main() {
    int t, e, a, b, p, q, r;
    cin >> t;
    while (t--) {
        cin >> n >> e;
        for (int i = 0; i < e; i++) {
            cin >> a >> b;
            V[a].push_back(b);
            V[b].push_back(a);
            cap[a][b] = 1;
            //cap[b][a] = 1;
        }
        cin >> p >> q >> r;
        //cout << edmond(p, q);
        if (edmond(p, q) <= r)
            cout << "NO\n";
        else
            cout << "YES\n";
    }
    return 0;
}