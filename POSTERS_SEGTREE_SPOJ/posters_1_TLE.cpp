#include <bits/stdc++.h>
using namespace std;
#define _ iso_base::sync_with_stdio(false);cin.tie(NULL);

#define ll long long
#define ff first
#define ss second
#define NND (ND << 1)
#define MID ((BEG+END)>>1)
bitset<50000005> segtree;



// update(1, 1, 10000000, vec[ii].ff, vec[ii].ss);
void update(int ND, int BEG, int END, int i, int j){
        // cout << "Start Update BEG: " << BEG << ", END: " << END << endl;
    if (j < BEG || i > END || i > j){
        return;
    }

    if (BEG == END){
        // cout << "this area is covered. BEG: " << BEG << ", END: " << END << endl;
        segtree[ND] = 0;
        return;
    }

    if (j <= MID) {
        // left subtree
        // cout << "Update Left tree" << endl;
        update(NND, BEG, MID, i, j);

    } else if (i > MID) {
        // right subtree
        // cout << "Update Right tree" << endl;
        update(NND+1, MID+1, END, i, j);
    } else {
        // cout << "Update Both tree" << endl;
        update(NND, BEG, MID, i, j);
        update(NND+1, MID+1, END, i, j);
    }

    segtree[ND] = segtree[ND] && (segtree[NND] || segtree[NND+1]);
}

bool query(int ND, int BEG, int END, int i, int j){
    if (BEG > j || END < i || i > j){
        return false;
    }

    if (!segtree[ND]) {
        // 完全被覆蓋過了
        return false;
    }

    if (BEG >= i && END <= j){
        return segtree[ND];
    }

    if (j <= MID) {
        // left subtree
        return query(NND, BEG, MID, i, j);

    } else if (i > MID) {
        // right subtree
        return query(NND+1, MID+1, END, i, j);
    } 

    bool left = query(NND, BEG, MID, i, j);
    bool right = query(NND+1, MID+1, END, i, j);

    return left | right; // 有一個 1 (曾經被覆蓋過) 就是true

}


int main(){
    int tc;
    cin >> tc;
    while(tc--){ // 沒有test case 計數 ith 問題, 直接while-- 即可
        int n_poster;
        int ans = 0;
        segtree.set(); // init segtree to 1

        cin >> n_poster;
        vector<pair<int, int> > vec;

        for (int ii = 0; ii < n_poster; ii++){
            int i, j;
            cin >> i >> j;
            vec.push_back(make_pair(i, j));
        }

        for (int ii = n_poster-1; ii > -1;--ii){
            // cout << "Now running (" << vec[ii].ff << ", " << vec[ii].ss << ")" << endl;
            if (query(1, 1, 10000000, vec[ii].ff, vec[ii].ss)){
                ans ++;
                update(1, 1, 10000000, vec[ii].ff, vec[ii].ss);
            }
        }

        cout << ans << endl;
    }
    return 0;
}