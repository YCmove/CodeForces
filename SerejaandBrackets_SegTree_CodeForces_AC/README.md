# [CodeForces - Sereja and Brackets](https://codeforces.com/contest/380/problem/C)
- [o1 reference](https://sidhantgoyal.wordpress.com/2014/02/05/sereja-and-brackets/)
  - CMB 已經是個完整的Brackets系統 ()(), ((()()))
  - Longest CMB for parent = Longest CMB for left child + Longest CMB for right child + min(unmatched left child ‘(‘ , unmatched right child ‘)’ )


# Notes
- Use 3 Different Segment Tree to Compute Final result
  - number of left brackets
  - number of right brackets
  - number of matched pairs, PS: "(())" counts for 4