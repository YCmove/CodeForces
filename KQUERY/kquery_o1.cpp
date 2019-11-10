// https://github.com/gabrielrussoc/competitive-programming/blob/master/spoj/kquery.cpp
#include <bits/stdc++.h>
#define ff first
#define ss second
using namespace std;
typedef pair<int,int> pii;
//        N = MAX, the number of origin number sequence length
//        Q = MAXQ, the number of k-queries
// MYQ
const int N = 30004, Q = 200007;
int bit[N];
int n, q, ans[Q]; // # of queries == # of answers
pii v[N]; // pair of two int


template<class T> void print_pair(T & p, int n){
    for(int i = 0; i < n; i++)
    {
        cout << p[i].ff << ", " << p[i].ss << endl;
    }
    cout << endl;
}


template<class T> void print_query(T & q, int n){
    for(int i = 0; i < n; i++)
    {
        cout << q[i].k << " ";
    }
    cout << endl;
}

struct colombo {
    // i, j, k  is the input query
    int i, j, k, o;

    // change the default sort function
    // sort colombo with o
    bool operator < (const colombo& x) const {
        return o < x.o;
    }
} query[Q];

// k is the value to compare with (greater than k)
// k值由大到小排列
bool compk(colombo a, colombo b){ return a.k > b.k; }

// insert BIT
void update(int idx, int val){
    // val == 1 代表 經過就+1
    for(int i = idx; i <= n; i += i&-i){
        bit[i] += val;
        cout << "bit[i]: " << bit[i] << " / i: " << i << endl;
    }
}

int qry(int idx){
    int sum = 0;
    for(int i = idx; i > 0; i -= i&-i)
        sum += bit[i];
    return sum;
}

int main(){
    scanf("%d",&n);
    // initialize BIT
    for(int i = 0; i <= n; i++) {
        bit[i] = 0;
    }

    // read in sequence of origin numbers
    for(int i = 0; i < n; i++){
        // v is pair of two int (ff, ss) represent the first and second of the pair
        scanf("%d", &v[i].ff); // ff is origin value
        v[i].ss = i+1; // ss is origin order, 從1開始
    }

    // BIT template start, First sort (sort the origin sequence)
    // print_pair(v, n);
    sort(v, v+n); // sort by ff (origin value) 由小到大
    // print_pair(v, n);
    // return 0;

    // read in queries
    scanf("%d",&q);
    for(int i = 0; i < q; i++){
        scanf("%d %d %d", &query[i].i, &query[i].j, &query[i].k);
        query[i].o = i;
    }

    // BIT template, Second sort (sort the query in descending order)
    // print_query(query, q);
    sort(query, query+q, compk);
    // 以k值由大到小排序
    // print_query(query, q);
    // return 0;

    // v: order by origin number value(由小到大)
    // query: order by k value (由大到小)
    int j = n-1;
    for(int i = 0; i < q; i++){
        // 題目要問的 v[j].ff > query[i].k
        while(j >= 0 && v[j].ff > query[i].k){
            cout << "i: " << i << " / j: " << j << endl;
            // void update(int idx, int val)
            // idx = v[j--].ss is BIT[idx], ss is index
            cout << "i: " << i << " / j: " << j << " / v[j].ff: " << v[j].ff << " / query[i].k: " << query[i].k << endl;
            cout << "--- Start Update ---" << endl;
            update(v[j--].ss, 1);
        }
        ans[query[i].o] = qry(query[i].j) - qry(query[i].i -1); // why 減一?
    }

    for(int i = 0; i < q; i++){
        printf("%d\n",ans[i]);   
    }
}