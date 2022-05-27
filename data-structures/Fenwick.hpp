#include <bits/stdc++.h>
using namespace std;

// Source: Lain
// Tested on: https://judge.yosupo.jp/problem/point_add_range_sum
//
// Implementation of a Fenwick Tree. `find_last_prefix` can be used to make
// a order-statistics tree.
template <typename T>
struct Fenwick {
 public:
  Fenwick() = default;
  Fenwick(int n) : n(n), tree(n + 1, 0) {}
  Fenwick(const vector<T>& build) : Fenwick(build.size()) {
    for (int i = 1; i <= n; i++) {
      tree[i] = build[i - 1];
      for (int k = (i & -i) >> 1; k > 0; k >>= 1) tree[i] += tree[i - k];
    }
  }

  void add(int pos, const T& change) {
    assert(pos < n);
    for (int i = pos + 1; i <= n; i += (i & -i)) tree[i] += change;
  }

  T query(int r) {
    assert(r < n);
    T ret = 0;
    for (int i = r + 1; i > 0; i -= (i & -i)) ret += tree[i];
    return ret;
  }

  T query(int l, int r) {
    return (l == 0) ? query(r) : query(r) - query(l - 1);
  }

  // Returns the largest p in [0,tn] such that query(p) <= sum
  int find_last_prefix(T sum) {
    if (sum < 0) return -1;
    int prefix = 0;
    for (int k = 31 - __builtin_clz(n); k >= 0; k--) {
      if (prefix + (1 << k) <= n && tree[prefix + (1 << k)] <= sum) {
        prefix += 1 << k;
        sum -= tree[prefix];
      }
    }
    return prefix;
  }

 private:
  size_t n;
  vector<T> tree;
};
