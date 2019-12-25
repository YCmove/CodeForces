#include <bits/stdc++.h>
using namespace std;
int n, m;
const int MAXN = 30011 + 1;
const int MAXM = 50011 + 1;
vector<vector<int> > g;
bool vis[MAXN];

int main(){
    int test_n;
    cin >> test_n;

    while(--test_n){
        cin >> n >> m;
        int a, b;
        while(--m){
            cin >> a >> b;

            // init
            g.clear();
            g.resize(n);
            g[a].push_back(b);
            for(int i = 0; i < n;++i){
                vis[i] = false;
            }

        }
    }
    return 0;
}