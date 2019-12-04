# [Huffman Decoding - Hacker Rank](https://www.hackerrank.com/challenges/tree-huffman-decoding/problem)

# C++ Notes
- [character frequency](https://www.geeksforgeeks.org/print-characters-frequencies-order-occurrence/)
```
// 'freq[]' implemented as hash table 
int freq[SIZE]; 

// initialize all elements of freq[] to 0 
memset(freq, 0, sizeof(freq)); 

// accumulate freqeuncy of each character in 'str' 
for (int i = 0; i < n; i++) 
    freq[str[i] - 'a']++; 
```
