#include <bits/stdc++.h>
using namespace std;

// Source: Lain
// Tested on : Yosupo Point Add Range Sum
// Implicit segment tree
// Requires manual editing to use for different tasks
// TODO: Make more modular to make editing easier
struct SegTreeNode {
  int l, r;
  SegTreeNode *left_child = nullptr, *right_child = nullptr;

  // Segtree data
  int64_t sum = 0;

  // Segment for range [lb,rb]
  SegTreeNode(int lb, int rb) : l(lb), r(rb) {}

  void extend() {
    if (left_child == nullptr && l + 1 <= r) {
      int M = (l + r) / 2;
      left_child = new SegTreeNode(l, M);
      right_child = new SegTreeNode(M + 1, r);
    }
  }

  void update(int pos, int val) {
    extend();
    if (left_child) {
      if (pos <= left_child->r)
        left_child->update(pos, val);
      else
        right_child->update(pos, val);
      sum = left_child->sum + right_child->sum;  // Combine results
    } else                                       // leaf node
      sum += val;
  }

  int64_t query(int ql, int qr) {
    if (ql <= l && r <= qr) return sum;
    if (max(l, ql) > min(r, qr))  // no intersection, segtree identity
      return 0;
    extend();
    return left_child->query(ql, qr) + right_child->query(ql, qr);
  }
};
