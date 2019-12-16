#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define Grafo vector<vector<ll>>

using namespace std;

ll visited[101010];
Grafo grafo;

ll dfs(ll i) {
    visited[i] = 1;
    ll gifts = 1;
    for (auto v : grafo[i]) {
        if (!visited[v]) {
            gifts += dfs(v);
        }
    }
    return gifts;
}

int main() {
    ll n, m, k;
    scanf("%lld %lld %lld", &n, &m, &k);
    grafo.resize(n);

    while (m--) {
        ll a, b;
        scanf("%lld %lld", &a, &b);
        a--;
        b--;
        grafo[a].pb(b);
    }

    ll resp = -1;

    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < n; j++){
            visited[j] = 0;
        }
        ll val = dfs(i);
        if (val < resp || resp == -1) {
            resp = val;
        }
    }
    printf("%lld\n", resp * k);
}