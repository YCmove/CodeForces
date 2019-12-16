#include <bits/stdc++.h>
// #define pb push_back
#define rep(i, n) for(int i=0; i<n; ++i)
// #define DiGraph vector<int>

using namespace std;
// typedef long long ll;

bool visited[1001];
vector<int> digraph[1001];
int steps = 0;
int n, m, weight;

void initial(){
    for (int i = 0; i <= 1001; ++i){
        visited[i] = false;
    }
}

void dfs(int node){
    // if (visited[node]){
    //     cout << "return node=" << node << '\n';
    //     return;
    // }
    steps++;
    // cout << "DFS node=" << node << ", size()=" << digraph[node].size() << '\n';
    visited[node] = true;

    for (auto itr = digraph[node].begin(); itr != digraph[node].end(); ++itr){
        // cout << "neighbor=" << *itr << ", visited[*itr]=" << visited[*itr]<< '\n';
        if(!visited[*itr]){
            dfs(*itr);
        }
    }
}

int main(){
    cin >> n >> m >> weight;
    // cout << "n="<< n << ", m=" << m << ", weight=" << weight << '\n';
    // initial();
    int minimum = INT_MAX;

    int a, b;
    for(int i = 0; i < m; ++i){
        cin >> a >> b;
        // cout << "a=" << a << ", b=" << b << '\n';
        digraph[a].push_back(b);
    }
    // cout << digraph[1].size() << '\n'; 
    // cout << digraph[2].size() << '\n'; 
    // cout << digraph[3].size() << '\n'; 
    // return 0;

    // 對每個點做dfs, 做steps
    for(int i = 1; i<=n; ++i){
        steps = 0;
        initial();
        // cout << "\nStart this node: " << i << '\n';
        dfs(i);
        if (steps < minimum){
            minimum = steps;
        }
        // cout << "minimum=" << minimum << ", steps=" << steps << ", i=" << i << '\n';
    }

    cout << minimum * weight << '\n';

    return 0;
}