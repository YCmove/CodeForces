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
    cin >> n;
    string s;
    cin >> s;

    // 每個字母能夠出現的長度上限
    vector<int> a(N);
    for(int p = 0; p < N; p++){
        cin >> a[p];
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
    ***/
    for(int p = 1; p <= n; p++){
        int allowed(n + 1);
        minNumber[p] = n + 1;

        for(int q = p - 1; q >= 0; q--){
            cout << "p: " << p << " / q: " << q << endl;

            long length = p - q;
            // s 為讀入的string (要傳出去的text)
            allowed = (allowed < a[s[q] - 'a']) ? allowed : a[s[q] - 'a'];

            if(length > allowed){
                break;
            }

            // ways[p] += ways[q]; ways[p] %= MOD;
            // minNumber[p] = (minNumber[p] < minNumber[q] + 1) ? minNumber[p] : (minNumber[q] + 1);
            // maxLength = (maxLength > length) ? maxLength : length;
        }
    }

    // cout << ways[n] << "\n" << maxLength << "\n" << minNumber[n] << endl;

    return 0;
}