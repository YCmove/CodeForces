#include <iostream>
#include<bits/stdc++.h> 

using namespace std;

int main() {
    int n,myMax =0;
    string str;
    cin >> n;
    map<string,int> strMap;
    for ( int i = 0 ; i<n ; i++){
        cin >> str;
        sort(str.begin(), str.end());
        strMap[str] ++;
        myMax =max(myMax,strMap[str]);
    }
    cout << myMax << endl;
    return 0;
}