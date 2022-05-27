#include "../utility/PBDS.hpp"
#include "bits/extc++.h"
using namespace std;

// Source: Me
// Tested on: CF 1093 E
// Count number of points in a rectangle with add/remove
// point queries online in O(log2n) with O(nlogn) memory
// Ordered set can be swapped out with treap
// x can range from [1,n]
struct RectangleCount {
  int n;
  vector<ordered_set<pair<int, int>>> points;

  RectangleCount(int _n) : n(_n), points(_n + 1) {}

  void insert(int x, int y) {
    for (int i = x; i <= n; i += i & -i) points[i].insert({y, x});
  }

  void erase(int x, int y) {
    for (int i = x; i <= n; i += i & -i) points[i].erase({y, x});
  }

  int query(int x, int y) {
    int res = 0;
    for (; x > 0; x -= x & -x) res += points[x].order_of_key({y, 1e9 + 7});
    return res;
  }

  // Find number of points in the rectangle [lx,rx] x [ly,ry]
  int query(int lx, int rx, int ly, int ry) {
    return query(rx, ry) - query(lx - 1, ry) - query(rx, ly - 1) +
           query(lx - 1, ly - 1);
  }
};
