#include <bits/stdc++.h>
using namespace std;

// My simple use lazy segtree
template<class T>
struct LazySegTree {
  int n;
  vector<T> t, lz;
  T E = 0;
  T ID = 0;

  T comb(T a, T b) { // Segtree function
    return a+b;
  }
  void push(int node, int l, int r) { // Propagation
    t[node] += (r-l+1)*lz[node];
    if (l != r) { // Propagate
      for (int it = 0; it < 2; it++){
        lz[2*node+it] += lz[node];
      }
    }
    lz[node] = ID;
  }
  LazySegTree() {}
  LazySegTree(int _n) : n(_n), t(4*n+5), lz(4*n+5) {
  }
  LazySegTree(vector<T>& bld) : n(bld.size()), t(4*n+5), lz(4*n+5) {
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
  void apply(int l, int r, T val) { apply(l,r,val,1,0,n-1); }
  void apply(int l, int r, T val, int node, int tl, int tr) {
    push(node,tl,tr);
    if (r < tl || tr < l) return;
    if (l <= tl && tr <= r) {
      lz[node] = val;
      push(node,tl,tr);
      return;
    }
    int tm = (tl+tr)/2;
    apply(l,r,val,2*node,tl,tm);
    apply(l,r,val,2*node+1,tm+1,tr);
    pull(node);
  }
  T query(int l, int r) {return query(l, r,1,0,n-1);}
  T query(int l, int r, int node, int tl, int tr) {
    push(node,tl,tr);
    if (r < tl || tr < l) return E;
    if (l <= tl && tr <= r) return t[node];
    int tm = (tl+tr)/2;
    return comb(query(l,r,2*node,tl,tm), query(l,r,2*node+1,tm+1,tr));
  }
};
