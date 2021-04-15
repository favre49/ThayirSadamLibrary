#include <bits/stdc++.h>
using namespace std;

template <class T = int>
struct Fenwick {
  vector<T> t;
  T tn;

  Fenwick(int _n) {
    assert(_n > 0);
    tn = _n;
    t = vector<T>(tn+1,0);
  }

  void update(int x, T val) {
    x++;
    while (x <= tn) {
      t[x] += val;
      x += (x&-x);
    }
  }

  // Find sum in [0..x]
  T query(int x) {
    assert(x < tn);
    x++;
    int res = 0;
    while (x > 0) {
      res += t[x];
      x -= (x&-x);
    }
    return res;
  }

  // Find sum in [l..r]
  T query(int l, int r) {
    assert(l <= r);
    if (l==0)
      return query(r);
    return query(r)-query(l-1);
  }

  // Returns the largest p in [0,tn] such that query(p) <= sum
  int find_last_prefix(T sum){
    if (sum < 0)
      return -1;
    int pref = 0;
    for (int k = 31 - __builtin_clz(tn); k >= 0; k--) {
      if (pref + (1<<k) <= tn && t[pref+(1<<k)] <= sum){
        pref += 1<<k;
        sum -= t[pref];
      }
    }
    return pref;
  }
};
