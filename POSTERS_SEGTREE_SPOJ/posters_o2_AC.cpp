#include<bits/stdc++.h>
#define mp make_pair
#define pb push_back
#define F first
#define S second
#define MOD 1000000007
//  (1 <= li < ri <= 10^7)
#define len 50000005
#define ZERO 1e-9
using namespace std;
#define _ ios_base::sync_with_stdio(false); cin.tie(NULL);

// 在此 segment_tree 只紀錄 1 or 0
// 另外使用 ans++ 來計算露出的海報

class segment_tree {
public:
    bitset<len> tree;
    int i, j;

    void build() {
        // set() 使bitset全部都初始化為 1 !!!
        // reset() 使bitset全部都初始化為 0
        tree.set();
    }

    //1 10 1 5
    // update(1, 1, 10000000, v[i].first, v[i].second);
    void update(int n, int s, int e, int q, int p) {
        // q, p 為要求ㄧquery的範圍，在整個遞迴中都不會去改變它們

        if (s == q && e == p) {
            cout << "this area is covered. s: " << s << ", e: " << e << endl;
            tree[n] = 0; // 已經被cover的區域就改成0
            return;
        }

        int left = n << 1;
        int right = left + 1;
        int mid = (s + e) >> 1;

        if (p <= mid) {
            // ALl in left tree
            update(left, s, mid, q, p);

        } else if (q > mid) {
            // All in right tree
            update(right, mid + 1, e, q, p);

        } else {
            // some in right/left tree
            update(left, s, mid, q, mid);
            update(right, mid + 1, e, mid + 1, p);
        }

        // tree[n] = 1 代表這個區域是空的(bitset全部初始化為1)
        // tree[n] = 0 代筆這個區域有東西覆蓋
        // 1 && 1 = 1 左右子樹必須要全空！ parent才會是空的
        // 0 && 1 = 0 只要左右子樹曾經被覆蓋過, parent就是0(下面的區域有被覆蓋了)
        cout << "tree[n]: " << tree[n] << " / tree[left]: " << tree[left] << " / tree[right]: " << tree[right] << endl;
        tree[n] = tree[n] && (tree[left] || tree[right]);

        // void 最後可以不用return
    }
 
    // t->query(1, 1, 10000000)
    bool query(int v, int a, int b) {
        // 注意 tree全部初始化為1
        if (a > b || a > j || b < i) {
            return false;
        }

        if (!tree[v]){
            // 代表這個區域都曾經被別人蓋過了！
            cout << "tree[v] is false" << endl;
            return false;
        }

        // Current segment is totally within range [i, j]
        if (a >= i && b <= j){
            cout << "tree[v] is true: " << tree[v] << endl;
            return tree[v];
        }

        // left, right 是segment tree上的index
        int left = v << 1;
        int right = left + 1;

        // mid 是實際上的值
        int mid = (a + b) >> 1; // (a+b)/2

        // left, right 是segment tree上的index
        // query(left, a, mid) 代表 從segment_tree[left]開始尋找, 範圍是a到mid
        // 0 || 0 = 0
        // 1 || 0 = 1 只要有一個1 就代表有空的面積！ 會露出來
        return query(left, a, mid) || query(right, mid + 1, b);
    }
};
 
int main(int argc, char **argv) {
    int tc, n, a, b;
    int ans;
    cin >> tc;

    vector<pair<int, int> > v;
    segment_tree *t = new segment_tree();

    // 不用紀錄 test case 的 order時（第i個） 就用 while(tc--) 即可
    while (tc--) {
        // init vector everytime
        v.clear();
        // init ans and segment tree
        ans = 0;
        t->build();

        cin >> n; // n is number of posters

        for (int i = 0; i < n; i++) {
            cin >> a >> b;
            v.push_back(make_pair(a, b));
        }

        // 從後面開始for loop, 因為有"覆蓋"過去的關係！
        for (int i = n - 1; i > -1; i--) { // AC
        // for (int i = 0; i < n; i++) { // WA
            t->i = v[i].first;
            t->j = v[i].second;
            cout << "Now running (" << v[i].first << ", " << v[i].second << ")" << endl;

            // bool query(int v, int a, int b) {
            if (t->query(1, 1, 10000000)) {
                // 第一個一定是 True, 一定會進來Loop, tree內什麼東西都沒有(tree bitset全部初始化為1)
                // 第二個就開始會有東西了
                ans++;
                cout << "Ans++" << endl;
                // void update(int n, int s, int e, int q, int p) {
                t->update(1, 1, 10000000, v[i].first, v[i].second);
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}