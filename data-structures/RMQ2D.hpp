#include <bits/stdc++.h>
using namespace std;

#include "../utility/Tensor.hpp"

// Source: Me
// Tested on: CF 1301 E
// 2D Sparse Table, finds MAXIMUM. Just change all max to min for MIN
template<typename T>
struct RMQ2D {
  int n,m;
  tensor<T,4> table;
  vector<int> logs;

  RMQ2D(vector<vector<T>>& matrix) {
    n = matrix.size();
    m = matrix[0].size();
    logs.resize(max(n,m)+1);
    int lgn = __lg(n)+1;
    int lgm = __lg(m)+1;
    table = tensor<T,4>({lgn,lgm,n,m});
    for (int i = 2; i <= max(n,m); i++) {
      logs[i] = logs[i-1];
      if ((1<<(logs[i]+1)) == i)
        logs[i]++;
    }
    for (int i =0; i < n; i++)
      for (int j = 0; j < m; j++)
        table[{0,0,i,j}] = matrix[i][j];
    for (int k = 1; k < lgn; k++)
      for (int i = 0; i +(1<<k) <= n; i++)
        for (int j = 0; j < m; j++)
          table[{k,0,i,j}] = max(table[{k-1,0,i,j}],table[{k-1,0,i+(1<<(k-1)),j}]);
    for (int l = 1; l < lgm; l++)
      for (int k = 0; k < lgn; k++)
        for (int i = 0; i+(1<<k) <= n; i++)
          for (int j = 0; j + (1<<l) <= m; j++)
            table[{k,l,i,j}] = max(table[{k,l-1,i,j}],table[{k,l-1,i,j+(1<<(l-1))}]);
  };

  // Query for maximum in the submatrix with top left (r1,c1) and bottom right
  // (r2,c2)
  T query(int r1, int c1, int r2, int c2) {
    if (r2 < r1 || c2 < c1 || r1 < 0 || r2 >= n || c1 < 0 || c2 >= m) return -1e8;
    int a = logs[(r2-r1)+1];
    int b = logs[(c2-c1)+1];
    return max({table[{a,b,r1,c1}],table[{a,b,r2-(1<<a)+1,c1}],table[{a,b,r1,c2-(1<<b)+1}], table[{a,b,r2-(1<<a)+1,c2-(1<<b)+1}]});
  }
};

