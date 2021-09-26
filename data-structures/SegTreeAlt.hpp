#include <bits/stdc++.h>
using namespace std;

// Source: Me
// Tested on: ???
// More general segtree. Remember to set identities
struct SegTree {
  struct T { // Segtree data
    int64_t sz = 0, sum = 0;
    T() {} // identity
    T(int x) : sum(x) {}
    friend T operator+(const T& a, const T& b) { // Combine two data
      T res;
      res.sz = a.sz + b.sz;
      res.sum = a.sum + b.sum;
      return res;
    }
  };
  int n;
  vector<T> t;
  SegTree() {}
  SegTree(vector<T>& v) {
    n = 1;
    while(n < v.size()) n *= 2;
    t.resize(2*n);
    for (int i = 0; i < v.size(); i++) t[n+i] = v[i];
    for (int i = n-1; i >= 1; i--) pull(i);
  }
  void pull(int node) {
    t[node] = t[2*node] + t[2*node+1];
  }
  T query(int l, int r) { return query(l,r,1,0,n-1); }
  T query(int l, int r, int node, int tl, int tr) {
    if (tr < l || tl > r) return T();
    if (l <= tl && tr <= r) return t[node];
    int tm = (tl+tr)/2;
    return query(l,r,2*node,tl,tm) + query(l,r,2*node+1,tm+1,tr);
  }
  void update(int p, T x) { return update(p,x,1,0,n-1); }
  void update(int p, T x, int node, int tl, int tr) {
    if (tl == tr) {
      t[node] = t[node] + x;
      return;
    }
    int tm = (tl+tr)/2;
    if (p <= tm) update(p,x,2*node,tl,tm);
    else update(p,x,2*node+1,tm+1,tr);
    pull(node);
  }
};
