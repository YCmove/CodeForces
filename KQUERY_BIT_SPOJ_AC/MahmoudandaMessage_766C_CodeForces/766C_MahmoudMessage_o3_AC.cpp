//https://www.cnblogs.com/TnT2333333/p/6690371.html
#include <iostream>
#include <cstring>
#define inf 0X3f3f3f3f
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
char s[1010];
int el[26] , MAX , MINF[1010];
ll dp[1010];


int main() {
    int n;
    cin >> n;
    cin >> s + 1;
    for(int i = 0 ; i < 26 ; i++) {
        cin >> el[i];
    }
    memset(dp , 0 , sizeof(dp));
    memset(MINF , inf , sizeof(MINF));
    
    dp[0] = 1 , MAX = 1 , MINF[0] = 0;

    for(int i = 1 ; i <= n ; i++) {
        for(int j = 1 ; j <= i ; j++) {
            int l = i - j + 1 , r = i;
            int flag = 0;
            for(int k = l ; k <= r ; k++) {
                int len = r - l + 1;
                if(el[s[k] - 'a'] < len) {
                    flag = 1;
                    break;
                }
            }
            if(!flag) {
                dp[i] = (dp[i] + dp[i - j]) % mod;
                MINF[i] = min(MINF[i] , MINF[i - j] + 1);
                MAX = max(MAX , j);
            }
        }
    }
    cout << dp[n] << endl;
    cout << MAX << endl;
    cout << MINF[n] << endl;
    return 0;
}