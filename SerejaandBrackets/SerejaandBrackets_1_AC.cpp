#include<bits/stdc++.h>
#define MX 5000005
#define MID (BEG+END)/2
#define NND (ND << 1)

using namespace std;
#define _ ios_base::sync_with_stdio(false); cin.tie(NULL);

// global
// ND, NND 從1開始, 是給三個segment tree所使用, 所以NND才是 2*ND (+1)
// BEG, END, MID 從0開始, 是給原始brackets_str使用
int open[MX], clos[MX], cnt[MX];
string brackets_str;

void creat_segtree(int ND, int BEG, int END){
    // 初始化三個segment tree
    if (BEG == END){
        // 設定最後一個
        // 注意！！！ 使用單引號
        brackets_str[BEG] == '(' ? open[ND]++ : clos[ND]++;
        return;
    }

    creat_segtree(NND, BEG, MID);
    creat_segtree(NND + 1, MID+1, END);
    int minc = min(open[NND], clos[NND + 1]);

    open[ND] = open[NND] + open[NND + 1] - minc;
    clos[ND] = clos[NND] + clos[NND + 1] - minc;
    cnt[ND] = cnt[NND] + cnt[NND + 1] + 2 * minc;
    // cout << "open[ND]: " << open[ND] << " / clos[ND]: " << clos[ND] << " / cnt[ND]: " << cnt[ND] << endl;
    return;
}

class info{
    public:
        int open, clos, cnt;
        info(int x=0, int y=0, int z=0):open(x), clos(y), cnt(z){}
};

info query(int ND, int BEG, int END, int L, int R){
    info left, right;
    // cout << "========= Recursive Start Query =========" << endl;
    // cout << "ND: " << ND << " / BEG: " << BEG << " / END: " << END << " / L: " << L << " / R: " << R << endl;
    // 依照 BEG, END 從seg tree 一路尋找
    // L, R 從頭到尾不會改變
    // 踢掉違法的
    if (L > END || R < BEG) {
        return info(0, 0, 0);
    }

    // if (BEG == END) {
    //     return info(0, 0, 0);
    // }

    // inside the right range
    if (L <= BEG && R >= END) {
        // cout << "--- Inside Range ---" << endl;
        // cout << "BEG: " << BEG << " / END: " << END << endl;
        // cout << "open[ND]: " << open[ND] << " / clos[ND]: " << clos[ND] << " / cnt[ND]: " << cnt[ND] << endl;
        return info(open[ND], clos[ND], cnt[ND]);
    }

    // cout << " --- Going Down Left subtree --- " << endl;
    left = query(NND, BEG, MID, L, R);
    // cout << " --- Going Down Right subtree --- " << endl;
    right = query(NND+1, MID+1, END, L, R);
    int minc = min(left.open, right.clos);

    info parent = info(left.open + right.open - minc, left.clos + right.clos - minc, left.cnt + right.cnt + 2 * minc);
    return parent;
}



int main(){
    cin >> brackets_str;
    int len = (int)brackets_str.length();
    creat_segtree(1, 0, len-1);
    // cout << "len: " << len << endl;
    // return 0;

    int n_query, l, r;
    cin >> n_query;
    while(n_query--){
        cin >> l >> r;
        // cout << "====== First Start Query ======" << endl;
        // cout << "Start Query - l: " << l << " / r: " << r << endl;
        // info query(int ND, int BEG, int END, int L, int R){
        // cout << "Start Query - len: " << len << endl;
        info result = query(1, 0, len-1, l-1, r-1);
        cout << result.cnt << endl;
    }


    return 0;
}