#include <bits/stdc++.h>
#include "Matrix.hpp"
using namespace std;


// Source: hitonanode
// Tested on: https://judge.yosupo.jp/problem/system_of_linear_equations
// Solve a system of linear equations
// Returns {{},{}} if no solution
// Otherwise returns {solution, basis of solution space}
// Rank = |basis of solution space|
template <typename T>
pair<vector<T>, vector<vector<T>>> system_of_linear_equations(Matrix<T> A, vector<T> b) {
  int n = A.N(), m = A.M();
  Matrix<T> M(n, m + 1);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) M[i][j] = A[i][j];
    M[i][m] = b[i];
  }
  M = M.gauss_jordan();
  vector<int> ss(m, -1);
  for (int i = 0; i < n; i++) {
    int j = 0;
    while (j <= m and M[i][j] == 0) j++;
    if (j == m) { // No solution
      return {{}, {}};
    }
    if (j < m) ss[j] = i;
  }
  vector<T> x(m);
  vector<vector<T>> D;
  for (int j = 0; j < m; j++) {
    if (ss[j] == -1) {
      vector<T> d(m);
      d[j] = 1;
      for (int jj = 0; jj < j; jj++) {
        if (ss[jj] != -1) d[jj] = -M[ss[jj]][j] / M[ss[jj]][jj];
      }
      D.emplace_back(d);
    } else
      x[j] = M[ss[j]][m] / M[ss[j]][j];
  }
  return make_pair(x, D);
}


