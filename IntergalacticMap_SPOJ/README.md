# Vertex Disjoint Path
# Dinic Algorithms
[IM - Intergalactic Map](https://www.spoj.com/problems/IM/)

# C++ Notes
- **INF=0x3f3f3f3f**
- 0x3f3f3f3f的十進位制是1061109567，是10^9級別的（和0x7fffffff一個數量級），而一般場合下的資料都是小於10^9的，所以它可以作為無窮大使用而不致出現數據大於無窮大的情形。
    另一方面，由於一般的資料都不會大於10^9，所以當我們把無窮大加上一個資料時，它並不會溢位（這就滿足了“無窮大加一個有窮的數依然是無窮大”），事實上0x3f3f3f3f+0x3f3f3f3f=2122219134，這非常大但卻沒有超過32-bit int的表示範圍，所以0x3f3f3f3f還滿足了我們“無窮大加無窮大還是無窮大”的需求。