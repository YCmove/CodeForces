#include <algorithm>
#include <iostream>
#include <vector>
#define rep(i, n) for (int i =0; i<n; ++i)
using namespace std;

// 注意這個max值
const int kMaxN = 1e5 + 5;
int order[kMaxN];

// array of vector
vector<int> vertex[kMaxN]; // 第0個不放東西

bool vizited[kMaxN];
vector<int> df_order;

template<class T> void print_vertex(T arr, int n){
    // cout <<  << '\n';
    rep(i, n){
        cout << "\narr[i]" << i << ": " ;
        int vec_len = arr[i].size();
        for (int j=0; j < vec_len; ++j){
            cout << arr[i][j] << " ";
        }
    }
    cout << '\n';
}

void df(int node) {
    df_order.push_back(node);
    vizited[node] = true;
    for (auto itr : vertex[node]) {
        if (not vizited[itr]) {
            df(itr);
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> permutation(n);
    for (int i = 0; i < n; i += 1) {
        int x;
        cin >> x;
        permutation[i] = x; // [1,4,2,3]
        order[x] = i; // 照原本的順序！
    }

    for (int i = 0; i < m; i += 1) {
        int a, b;
        cin >> a >> b;
        // 無向圖
        vertex[a].push_back(b);
        vertex[b].push_back(a);
    }

    // print_vertex(vertex, n);

    for (int i = 1; i <= n; i += 1) {
        sort(vertex[i].begin(), vertex[i].end(), [&](int a, int b) {
            return order[a] < order[b];
        }); // 將全部子序列都按照原本input的順序
    }

    // print_vertex(vertex, n);

    df(1);

    cout << (permutation == df_order) << '\n';
    return 0;
}
