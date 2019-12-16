#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <iostream>
#include <map>
#include <set>
#include <utility>
#include <vector>

#define MX 100000
#define pb push_back
#define mp make_pair
#define fs first
#define sec second
#define sc scanf
#define pr printf

using namespace std;

vector<int> v[1001];
bool vis[1001];
int c;


void initial() {
    for (int i = 0; i <= 1001; ++i) {
        vis[i] = false;
    }
}


void dfs(int s) {
    vis[s] = true;
    c = c + 1;
    for (int i = 0; i < v[s].size(); ++i) {
        if (vis[v[s][i]] == false)
            dfs(v[s][i]);
    }
}


int main() {
    //freopen("t10.txt", "r", stdin);            //  line1
    //freopen("o10.txt", "w", stdout);
    int min = 10000000;
    int n, m, i, j, a, b, k;
    cin >> n >> m >> k;

    while (m--) {
        cin >> a >> b;
        v[a].push_back(b);
    }

    // 對每個點做dfs
    for (i = 1; i <= n; i++) {
        initial();
        c = 0;

        dfs(i);
        if (min > c){
            min = c;
        }
    }

    cout << min * k;
    return 0;
}
