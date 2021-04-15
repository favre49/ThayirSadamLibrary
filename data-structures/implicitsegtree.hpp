#include <bits/stdc++.h>
using namespace std;

struct SegTreeNode {
  // Node values
  int sum = 0;

  int left, right; // Segment bounds
  SegTreeNode *left_child = nullptr, *right_child = nullptr; // Children

  // Segment for range [lb,rb)
  SegTreeNode(int lb, int rb)
  {
    left = lb;
    right = rb;
  }

  void extend()
  {
    // Split the range into two equal subranges, if possible
    if (!left_child && left+1 < right)
    {
      int t = (left+right)/2;
      left_child = new SegTreeNode(left,t);
      right_child = new SegTreeNode(t,right);
    }
  }

  void update(int pos, int val)
  {
    extend();
    sum += val;
    if (left_child)
    {
      if (pos < left_child->right)
        left_child->update(pos,val);
      else
        right_child->update(pos,val);
    }
  }

  int query(int lq, int rq)
  {
    if (lq <= left && right <= rq)
      return sum;
    if (max(left,lq) >= min(right,rq))
      return 0;
    extend();
    return left_child->query(lq,rq) + right_child->query(lq,rq);
  }
};
