#include<bits/stdc++.h>
using namespace std;

template<class T>
struct SegTree {
  int n;
  vector<T> t;
  T E = 0;

  T comb(T a, T b) { // Segtree function
    return a+b;
  }
  SegTree() {}
  SegTree(int _n) : n(_n), t(4*n+5) {}
  SegTree(vector<T>& bld) : n(bld.size()), t(4*n+5) {
    build(bld,1,0,n-1);
  }
  void build(vector<T>& bld, int node, int tl, int tr) {
    if (tl == tr) {
      t[node] = bld[tl];
    }
    else {
      int tm = (tl+tr)/2;
      build(bld,2*node,tl,tm);
      build(bld,2*node+1,tm+1,tr);
      pull(node);
    }
  }
  void pull(int node) { t[node] = comb(t[2*node], t[2*node+1]); }
  T query(int l, int r) {return query(l, r,1,0,n-1);}
  T query(int l, int r, int node, int tl, int tr) {
    if (r < tl || tr < l) return E;
    if (l <= tl && tr <= r) return t[node];
    int tm = (tl+tr)/2;
    return comb(query(l,r,2*node,tl,tm), query(l,r,2*node+1,tm+1,tr));
  }
  void update(int p, T val) { return update(p,val,1,0,n-1); }
  void update(int p, T val, int node, int tl, int tr) {
    if (tl == tr) {
      t[node] += val;
      return;
    }
    int tm = (tl+tr)/2;
    if (p <= tm) update(p,val,2*node,tl,tm);
    else update(p,val,2*node+1,tm+1,tr);
    pull(node);
  }
};
