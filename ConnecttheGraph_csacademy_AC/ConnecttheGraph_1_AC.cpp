#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for(int i =0; i<n; ++i)

const int maxn = 1e5+5;

int n, m;

vector<int> graph[maxn];
vector<int> root_nodes; // component
int parent[maxn];
bool visited[maxn] = {false};
vector<pair<int, int> > free_edges;


void dfs(int node){
    visited[node] = true;
    // cout << "start dfs node=" << node << '\n';
    // return;
    
    for (auto itr : graph[node]){
        // cout << "itr=" << itr << '\n';
        // return;
        if (itr == parent[node]){
            continue;
        }
        
        if(!visited[itr]){
            parent[itr] = node;
            dfs(itr);
        } else if (itr < node){
            free_edges.push_back(make_pair(node, itr));
        }
    }

}



int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;
    int a, b;
    rep(i, m){
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    for (int i = 1; i <= n; ++i){
        if (!visited[i]){
            // cout << "i=" << i << '\n';
            root_nodes.push_back(i);
            dfs(i);
        }
    }

    // return 0;
    

    if (root_nodes.size() - 1 > free_edges.size()) {
        cout << "-1" << '\n';
        return 0;
    } else {
        cout << root_nodes.size() - 1 << '\n';
        while (root_nodes.size() > 1){
            int a = root_nodes.front();
            int b = root_nodes.back();
            root_nodes.pop_back();

            auto deleted_edges = free_edges.back();
            free_edges.pop_back();

            cout << deleted_edges.first << ' ' << deleted_edges.second << ' ' << a << ' ' << b << '\n';
            
        }
    }


    return 0;
}