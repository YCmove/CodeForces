
#include <cstdio>
#include <cstring>
#include <functional>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
char str[1000];
int cnt[30];


template<typename T> void print_queue(T& q) {
    while(!q.empty()) {
        cout << q.top() << " ";
        q.pop();
    }
    cout << endl;
}

int main() {
    //freopen("data.txt","r",stdin);
    while (cin >> str) {
        if (!strcmp(str, "END")) break;
        memset(cnt, 0, sizeof(cnt));

        int len = strlen(str);
        for (int i = 0; i < len; i++) {
            if (str[i] == '_')
                cnt[26]++;
            else
                cnt[str[i] - 'A']++;
        }
        //C++ CE,G++ AC
        priority_queue<int, vector<int>, greater<int>> q;
        for (int i = 0; i <= 26; i++) {
            if (cnt[i]) {
                q.push(cnt[i]);
            }
        }

        // print_queue(q);
        // continue;

        int sum = 0;
        while (q.size() > 1) {
            int x = q.top();
            q.pop();
            int y = q.top();
            q.pop();
            q.push(x + y);
            sum += (x + y);
            // cout << "q.size()=" << q.size() << ", x=" << x << ", y=" << y << ", sum=" << sum <<'\n' << "=========\n";

        }
        if (sum == 0) //只有一个元素
            sum = len;
        printf("%d %d %.1lf\n", len * 8, sum, (len * 8.0) / (sum * 1.0));
    }
    return 0;
}