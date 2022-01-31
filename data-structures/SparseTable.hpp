#include <bits/stdc++.h>
using namespace std;

// Source: me
// Tested on: CF 1632 D
// Sparse table for O(1) queries on idempotent functions
template <typename T>
struct SparseTable {
  size_t n, log;
  vector<vector<T>> st;
  vector<int> log_table;
  const T ID = 0; // identity element

  T op(T x, T y) const { // Must be idempotent, i.e. f(x,x) = x
    return __gcd(x,y);
  }

  SparseTable() {}
  SparseTable(const vector<T>& a) : n(a.size()) {
    log_table.resize(n+1);
    for (int i = 2; i <= n; i++)
      log_table[i] = log_table[i>>1]+1;
    log = log_table[n]+1;
    st.assign(log,vector<T>(n,ID));
    st[0] = a;
    for (int j = 1; j < log; j++)
      for (int i = 0; i + (1<<j) <= n; i++)
        st[j][i] = op(st[j-1][i],st[j-1][i+(1<<(j-1))]);
  }

  // Query range [l,r]
  T query(int l, int r) const {
    assert(l >= 0 && l <= r && r < n);
    int j = log_table[r-l+1];
    return op(st[j][l],st[j][r-(1<<j)+1]);
  }
};


