#include<bits/stdc++.h>
using namespace std;



int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n; cin >> n;
    int curr_max = 0;
    string str;
    map<string, int> m;

    while(n--){
        cin >> str;
        // cout << str << '\n';
        // 完全不用去紀錄a, b, c 每個字母的出現次數
        // sorting後就可以解決題目需求
        sort(str.begin(), str.end());
        m[str]++;
        curr_max = max(curr_max, m[str]);
    }

    cout << curr_max << endl;





    return 0;
}