#include<bits/stdc++.h>

using namespace std;
// lowbit 從低位數來第一個非零位數
#define lowbit(x) ((x)&(-x))
#define ff first
#define ss second
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);

// global variable for BIT
#define MAXN 30005
#define MAXQ 200005
int n_num, n_qry, ans[MAXQ];
int BIT[MAXN+2];
pair<int, int> nums[MAXN];

struct q_elem{
    int i, j, k, order;
    // bool operator < (const q_elem& x) const {
    //     return order < x.order;
    // }
} query[MAXQ];


template<class T> void print_pair(T & p, int n){
    for (int i = 0; i < n; ++i){
        cout << p[i].ff << " ";
    }
    cout << endl;
}

template<class T> void print_query(T & q, int n){
    for (int i = 0; i < n; ++i){
        cout << q[i].k << " ";
    }
    cout << endl;
}

bool comp(q_elem & a, q_elem & b){
    if (a.k == b.k){
        return a.order > b.order;
    }
    return a.k > b.k;
}

// BIT template for insert/update
void update(int idx, int val){
    // default val is always 1
    while(idx <= n_num){
        BIT[idx] += val;
        // cout << "BIT[idx]: " << BIT[idx] << " / idx: " << idx << endl;
        idx += lowbit(idx);
    }
}

// BIT template for query
int qry(int idx){
    int sum = 0;
    while (idx > 0){ // 不可以等於0, BIT[0]沒有設定任何值
        sum += BIT[idx];
        idx -= lowbit(idx);
    }
    return sum;
}


int main(){
    int num;
    cin >> n_num;
    for (int i = 0; i < n_num; ++i){
        cin >> num;
        nums[i].ff = num;
        nums[i].ss = i+1; // order從1開始, 因為query i, k的記數法！
    }
    // print_pair(nums, n_num);
    sort(nums, nums+n_num); // 依照first(num)做排列  由小到大
    // print_pair(nums, n_num);
    
    int n_qry;
    cin >> n_qry;
    for (int ii = 0; ii < n_qry; ++ii){
        int i, j, k;
        cin >> i >> j >> k;
        query[ii].order = ii;
        query[ii].i = i;
        query[ii].j = j;
        query[ii].k= k;
    }

    // print_query(query, n_qry);
    sort(query, query+n_qry, comp);
    // print_query(query, n_qry);
    int j = n_num - 1;
    for (int i = 0; i < n_qry; ++i){

        // 在此若使用if會黃金交叉....
        while (j >=0 && nums[j].ff > query[i].k){
            // Build BIT
            // cout << "i: " << i << " / j: " << j << " / nums[j].ff: " << nums[j].ff << " / query[i].k: " << query[i].k << endl;
            // cout << "--- Start Update ---" << endl;
            update(nums[j].ss, 1);
            j -= 1;
        }
        // for (; j>=0; --j){
        //     cout << "i: " << i << " / j: " << j << endl;
        //     if (nums[j].ff > query[i].k){
        //         // Build BIT
        //         cout << "i: " << i << " / j: " << j << " / nums[j].ff: " << nums[j].ff << " / query[i].k: " << query[i].k << endl;
        //         update(nums[j].ss, 1);
        //     }
        // }
        ans[query[i].order] = qry(query[i].j) - qry(query[i].i-1); // 減一！！
    }


    // print ans
    for (int i = 0; i < n_qry; i++){
        cout << ans[i] << endl;
    }


    return 0;
}