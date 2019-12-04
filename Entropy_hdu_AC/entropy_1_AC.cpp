/*
Consider the text “AAAAABCD”. Using ASCII, encoding this would require 64 bits.

If, instead, we encode “A” with the bit pattern “00”, “B” with “01”, “C” with “10”, and “D” with “11” then we can encode this text in only 16 bits; the resulting bit pattern would be “0000000000011011”.

This is still a fixed-length encoding, however; we’re using two bits per glyph instead of eight. Since the glyph “A” occurs with greater frequency, could we do better by encoding it with fewer bits? 

In fact we can, but in order to maintain a prefix-free encoding, some of the other bit patterns will become longer than two bits. An optimal encoding is to encode “A” with “0”, “B” with “10”, “C” with “110”, and “D” with “111”. (This is clearly not the only optimal encoding, as it is obvious that the encodings for B, C and D could be interchanged freely for any given encoding without increasing the size of the final encoded message.) 

Using this encoding, the message encodes in only 13 bits to “0000010110111”, a compression ratio of 4.9 to 1 (that is, each bit in the final encoded message represents as much information as did 4.9 bits in the original encoding).

Read through this bit pattern from left to right and you’ll see that the prefix-free encoding makes it simple to decode this into the original text even though the codes have varying bit lengths.

As a second example, consider the text “THE CAT IN THE HAT”. In this text, the letter “T” and the space character both occur with the highest frequency, so they will clearly have the shortest encoding bit patterns in an optimal encoding. The letters “C”, “I’ and “N” only occur once, however, so they will have the longest codes.

There are many possible sets of prefix-free variable-length bit patterns that would yield the optimal encoding, that is, that would allow the text to be encoded in the fewest number of bits. 

One such optimal encoding is to encode spaces with “00”, “A” with “100”, “C” with “1110”, “E” with “1111”, “H” with “110”, “I” with “1010”, “N” with “1011” and “T” with “01”. 

The optimal encoding therefore requires only 51 bits compared to the 144 that would be necessary to encode the message with 8-bit ASCII encoding, a compression ratio of 2.8 to 1.

*/

// #include <bits/stdc++.h>
#include <cstdio>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <string>
#include <functional>
#include <iostream>
#include <queue>
#include <vector>
#define SIZE 27
#define rep(i, n) for (int i=0; i<n; ++i)
using namespace std;


template<typename T> void print_queue(T& q) {
    while(!q.empty()) {
        cout << q.top() << " ";
        q.pop();
    }
    cout << endl;
}

int main(){
    string s;

    while(cin >> s){
        if (s == "END") return 0;
        // cout << s << '\n';
        int freq[SIZE];
        memset(freq, 0, sizeof(freq)); 

        // for (auto itr : s){
            // cout << itr << ' ';
        for (int i = 0; i < (int)s.size(); i++) {
            if (s[i] == '_'){
                freq[26] += 1;
            } else {
                freq[s[i] - 'A'] += 1;
            }
        }

        // priority_queue<int> pq;
        priority_queue<int, vector<int>, greater<int> > pq;
        rep(i, SIZE){
            if (freq[i] > 0) {
                // cout << "freq[i] = " << freq[i] << ", ";
                pq.push(freq[i]);
            }
        }

        // cout << "\n";
        // print_queue(pq);
        // continue;

        int sum = 0;
        // int n1, n2;
        // cout << "1. pq.size() = " << pq.size() << '\n';
        while (pq.size() > 1){
            int n1 = pq.top();
            pq.pop();
            int n2 = pq.top();
            pq.pop();
            // 記得還要放回去！！
            pq.push(n1+n2);
            sum += (n1+n2);
            // if (pq.size() != 1){
            //     sum += (n1+n2);
            //     cout << "pq.size()=" << pq.size() << ", n1=" << n1 << ", n2=" << n2 << ", sum=" << sum <<'\n' << "=========\n";
            // }
        }
        if (sum == 0){
            // n = pq.top();
            sum = s.size();
        }

        

        // output the length in bits of the 8-bit ASCII encoding
        // the length in bits of an optimal prefix-free variable-length encoding
        // the compression ratio accurate to one decimal point.

        // 居然是 printf.......
        printf("%d %d %.1lf\n", (int)s.size() * 8, sum, ((s.size() * 8.0)/(sum * 1.0)));
        // cout << s.size()*8 << ' ' << sum << ' ' <<  setprecision(2)  << s.size()*8.0 / sum*1.0 << '\n';

    }




    return 0;
}