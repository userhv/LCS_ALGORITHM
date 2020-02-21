Longest Common Subsequence in C.


<h3>Algorithm 1 Longuest Common Subsequence<\h>
  
1: function lcs(X, Y, m, n))
2: X : sequˆencia de m elementos [0...m-1]
3: Y : sequˆencia de n elementos [0...n-1]
4: m : tamanho de X
5: n : tamanho de Y
6:
7: L ← array[0...m][0...n]
8:
9: for i ← 0, i < m + 1, i + + do
10: for j ← 0, i < n + 1, j + + do
11: if i = 0 ∨ j = 0 then
12: L[i][j] ← 0
13: else if X[i − 1] = Y [j − 1] then
14: L[i][j] ← L[i − 1][j − 1] + 1
15: else
16: L[i][j] ← max(L[i − 1][j], L[i][j − 1])
17: end if
18: end for
19: end for
20:
21: index ← L[m][n]
22: LCS ← array[0...index − 1]
23:
24: i ← m
25: j ← n
26: while i > 0 ∧ j > 0 do
27: if X[i − 1] = Y [j − 1] then
28: LCS[index − 1] ← X[i − 1]
29: index ← index − 1
30: j ← j − 1
31: j ← j − 1
32: else if L[i − 1][j] > L[i][j − 1] then
33: i ← i − 1
34: else
35: j ← j − 1
36: end if
37: end while
38:
39: return LCS
40: end function
