#include <iostream>
#include <cstring>
using namespace std;

int main(){
    // int test(555);
    string s = "abcd";

    // 可以用來計算alphabet的order
    cout << s[0] - 'a' << '\n'; // 0
    cout << s[1] - 'a' << '\n'; // 1
    cout << s[2] - 'a' << '\n'; // 2
    cout << s[3] - 'a' << '\n'; // 3
    return 0;
}