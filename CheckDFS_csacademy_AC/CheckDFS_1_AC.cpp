#include <bits/stdc++.h>
#define rep(i, n) for (int i =0; i<n; ++i)
using namespace std;

const int maxn = 1e5+5;
int n, m;
vector<int> input_nums;
vector<int> graph[maxn];
int input_order[maxn];
bool visited[maxn] = {false};
vector<int> df_order;


void df(int node){
    df_order.push_back(node);
    visited[node] = true;
    for(auto itr : graph[node]){
        // cout << itr << " ";
        if(!visited[itr]){
            df(itr);
        }
    }
}


int main(){
    cin >> n >> m;
    
    int num;
    rep(i, n){
        cin >> num;
        input_nums.push_back(num);
        input_order[num] = i;
    }

    int a, b;
    rep(i, m){
        cin >> a >> b;
        // graph[0]沒有東西
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    for (int i = 1; i<=n; ++i){
        sort(graph[i].begin(), graph[i].end(), [&](int a, int b){
            return input_order[a] < input_order[b];
        });
    }

    df(1);

    cout << (df_order == input_nums) << '\n';

    return 0;
}