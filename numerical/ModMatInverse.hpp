#include <bits/stdc++.h>
using namespace std;

#include "../number-theory/ModInt.hpp"

// Source: KACTL
// Tested on: Yosupo Matrix Inverse
// Finds inverse of a matrix
// Returns the rank of a matrix, i.e. only inverted if
// rank == n
int inverse(vector<vector<mod_int>>& A) {
  int n = A.size();
  vector<int> col(n);
  vector<vector<mod_int>> tmp(n,vector<mod_int>(n));
  for (int i =0; i < n; i++) {
    tmp[i][i] = 1;
    col[i] = i;
  }
  for (int i = 0; i < n; i++) {
    int r = i, c =i;
    for (int j = i; j < n; j++) {
      for (int k = i; k < n; k++) {
        if (A[j][k] != 0) {
          r = j;
          c = k;
          goto found;
        }
      }
    }
    return i;
found:;
    A[i].swap(A[r]);
    tmp[i].swap(tmp[r]);
    for (int j =0; j < n; j++) {
      swap(A[j][i], A[j][c]);
      swap(tmp[j][i],tmp[j][c]);
    }
    swap(col[i],col[c]);
    mod_int v = A[i][i].inv();
    for (int j = i+1; j < n; j++) {
      mod_int f = A[j][i]*v;
      A[j][i] = 0;
      for (int k = i+1; k < n; k++)
        A[j][k] -= f*A[i][k];
      for (int k = 0; k < n; k++)
        tmp[j][k] -= f*tmp[i][k];
    }
    for (int j = i+1; j < n; j++)
      A[i][j] *= v;
    for (int j =0; j < n; j++)
      tmp[i][j] *= v;
    A[i][i] = 1;
  }
  for (int i = n-1; i >= 0; i--) {
    for (int j = 0; j < i; j++) {
      mod_int v = A[j][i];
      for (int k = 0; k < n; k++)
        tmp[j][k] -= v*tmp[i][k];
    }
  }
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      A[col[i]][col[j]] = tmp[i][j];
  return n;
}
