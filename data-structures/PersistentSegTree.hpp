#include <bits/stdc++.h>
using namespace std;

// Source: Me
// Tested on: ???
struct PersistentSegTree {
  struct SegTreeNode {
    SegTreeNode *l, *r; // Children

    // Node values
    int mx;

    SegTreeNode(int val=0) : l(nullptr),r(nullptr),mx(val) {}
    SegTreeNode(SegTreeNode *l, SegTreeNode *r) : l(l),r(r),mx(0) {
      if (l) mx = max(mx,l->mx);
      if (r) mx = max(mx,r->mx);
    }
  };

  vector<SegTreeNode*> roots; // History
  int L, R; // Bounds

  PersistentSegTree(int tl, int tr) : L(tl), R(tr) {
    roots.push_back(build(tl,tr));
  }

  int size() { return (int)roots.size(); }

  // Get node from history
  SegTreeNode*& operator[](int idx) {
    assert(idx < roots.size());
    return roots[idx];
  }

  // Build segtree
  SegTreeNode* build(int tl, int tr) {
    if (tl==tr)
      return new SegTreeNode(0);
    int tm = (tl+tr)/2;
    return new SegTreeNode(build(tl,tm),build(tm+1,tr));
  }

  // Query current node for range [l,r]
  int query(int l, int r) {
    return query(roots.back(),l,r,L,R);
  }

  // Query node ind for range [l,r]
  int query(int ind, int l, int r) {
    return query(roots[ind],l,r,L,R);
  }

  int query(SegTreeNode* v, int l, int r, int tl, int tr) {
    if (l > r) return 0;
    if (l == tl && r == tr) return v->mx;
    int tm = (tl+tr)/2;
    return max(query(v->l,l,min(r,tm),tl,tm),query(v->r,max(l,tm+1),r,tm+1,tr));
  }

  // Point update position pos to value val
  void update(int pos, int val) {
    roots.push_back(update(roots.back(),pos,val,L,R));
  }

  SegTreeNode* update(SegTreeNode* v, int pos, int val, int tl, int tr) {
    if (tl==tr)
      return new SegTreeNode(val);
    int tm = (tl+tr)/2;
    if (pos <= tm)
      return new SegTreeNode(update(v->l,pos,val,tl,tm),v->r);
    else
      return new SegTreeNode(v->l,update(v->r,pos,val,tm+1,tr));
  }
};
