#include<bits/stdc++.h>
using namespace std;
int n_char;
int alphabet[27];

template<class T> void print_arr(T * arr, int n){
    for (int i = 0; i < n; ++i){
        cout << arr[i] << " ";
    }
    cout << '\n';
}


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n_char;
    char arr[n_char];
    for (int i = 0 ; i < n_char; ++i){
        cin >> arr[i];
    }

    for (int i = 1 ; i < 27; ++i){
        cin >> alphabet[i];
    }

    // print_arr(alphabet, 27);

    return 0;
}