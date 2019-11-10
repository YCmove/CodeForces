// https://sidhantgoyal.wordpress.com/2014/02/05/sereja-and-brackets/
#include <bits/stdc++.h>
// #define FILL(x,y) memset(x,y,sizeof(x))

// MYQ why 5000005?
// max seq. length = 10^6 = 1000000
#define MX 5000005

// NND = ND << 1 往左移一位(*2^1)
#define NND (ND<<1) // ND可以位在

#define MID (BEG+END)/2

using namespace std;

// 三個線段樹, 開到最大5000005！ 起點是 1 (not 0)
int open[MX], clos[MX], cnt[MX];
string s;

class info{
    public:
    int open, clos, cnt;
    info(int X=0,int Y=0,int Z=0):open(X),clos(Y),cnt(Z){
    }
};

// 第一次初始化 init(1, 0, (int)s.length()-1);
void init(int ND, int BEG, int END){
    if(BEG==END){
        s[BEG]== '(' ? open[ND]++ : clos[ND]++;
        return; // 已經走完該子樹，直接return
    }

    // 第一次初始化時，使用NND=1*2=2為(ND=1)
    // 因為左子樹2x, 右子樹2x+1
    //********** Segment Tree的套路 **********
    // cout << "NND: " << NND << " / ND: " << ND << endl;
    init(NND, BEG, MID);
    init(NND + 1, MID + 1, END);
    // 注意這是取最小值
    int minc = min(open[NND], clos[NND + 1]);

    // "()" 計數是2, 故 minc*2
    cnt[ND] = cnt[NND] + cnt[NND + 1] + 2 * minc;

    // parent node = left subtree + right subtree - minc 
    // -minc 代表減掉配對成功的數量
    // open "(" 和 clos ")" 純粹計數，只要扣掉左右結合後配對成功的數字
    open[ND] = open[NND] + open[NND + 1] - minc;
    clos[ND] = clos[NND] + clos[NND + 1] - minc;
}

// 只需要query沒有modify
info q(int ND, int BEG, int END, int L, int R){
     
    info a1,a2;
    if(END < L or BEG > R){
        return info(0,0,0);
    }

    if(L <= BEG and END <= R){
        // 走進 segment tree 的範圍內
        // cout << "L <= BEG and END <= R" << endl;
        return (info(open[ND],clos[ND],cnt[ND]));
    }

    // cout << "BEG: " << BEG << " / END: " << END << " / L: " << L << " / R: " << R << endl;
    //********** Query 也是一樣 Segment Tree的套路 **********
    a1 = q(NND, BEG, MID, L, R);
    a2 = q(NND + 1, MID + 1, END, L, R);
    int minc = min(a1.open, a2.clos);
     
    return info(a1.open + a2.open - minc, a1.clos + a2.clos - minc, a1.cnt + a2.cnt + 2 * minc);
}


int main(){
    // string s
    cin>>s;
    // cout << "s: " << s << endl;
    // 建立線段樹
    init(1, 0, (int)s.length()-1);

    int m,l,r; cin>>m;
    while(m--){
        cin >> l >> r;
        // 只需要query沒有modify
        // info q(int ND, int BEG, int END, int L, int R){
        // L, R 是query的範圍
        cout << q(1, 0, s.length()-1, l - 1, r - 1).cnt << "\n";
    }
    return 0;
}