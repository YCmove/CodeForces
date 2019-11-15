// https://github.com/SongYuki/CodeForces-1/blob/master/766C-MahmoudAndAMessage.cpp
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

int main(){

    const int N = 26;
    const ll MOD = 1000000007;
    ios_base::sync_with_stdio(false);

    int n;
    cin >> n; // input string s 的長度
    string s;
    cin >> s;

    // 每個字母能夠出現的長度上限
    vector<int> alpha(N);
    // alpha 從 0 到 25
    for(int p = 0; p < N; p++){
        cin >> alpha[p];
    }

    // 3. 切成最少的 Substring 組合
    vector<int> minNumber(n + 1, 0);

    // 1. 問總共的組合數
    vector<ll> ways(n + 1, 0); ways[0] = 1;

    // 2. 最大substring長度
    int maxLength(0);

    /***
    p from 1 to 26
    p, q的配置
    p: 1 / q: 0
    p: 2 / q: 1
    p: 2 / q: 0
    p: 3 / q: 2
    p: 3 / q: 1
    p: 3 / q: 0

    利用p, q 可以組合出Substring的切割方式
    ***/
    for(int p = 1; p <= n; p++){
        int allowed(n + 1); // allowed是 origin input string 的長度再+1
        minNumber[p] = n + 1;

        for(int q = p - 1; q >= 0; q--){
            cout << "p: " << p << " / q: " << q << endl;

            // length 代表substring的長度
            long length = p - q;

            // s 為讀入的string (要傳出去的text)
            // 檢查每一個字母s[q]能夠出現的次數
                // cout << "alpha[s[q] - 'a']限制出現長度: " << alpha[s[q] - 'a'] << " / allowed: " << allowed << '\n';
            allowed = (allowed < alpha[s[q] - 'a']) ? allowed : alpha[s[q] - 'a'];

            if(length > allowed){
                // substring的長度超過了允許範圍，什麼時後是允許範圍呢？
                // 檢查每個字母的允許上限！
                cout << "length: " << length << " / allowed: " << allowed << '\n';
                break;
            }

            ways[p] += ways[q];
            ways[p] %= MOD;
            minNumber[p] = (minNumber[p] < minNumber[q] + 1) ? minNumber[p] : (minNumber[q] + 1);
            maxLength = (maxLength > length) ? maxLength : length;
        }
    }

    cout << ways[n] << "\n" << maxLength << "\n" << minNumber[n] << endl;

    return 0;
}