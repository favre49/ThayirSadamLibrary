#include <bits/stdc++.h>
using namespace std;

// Source: KACTL
// Tested on: Yosupo Judge Line Add Get Min
// Dynamic Convex Hull Trick, with two operations:
// 1. Insert line kx+m
// 2. Query maximum value at x
// TODO: Implementation using doubles via template enable_ifs
namespace internal_cht {
struct Line {
  mutable int64_t k, m, p;

  bool operator<(const Line& o) const { return k < o.k; }

  bool operator<(const int64_t x) const { return p < x; }
};
};  // namespace internal_cht

struct CHT : multiset<internal_cht::Line, less<>> {
 public:
  // Add line kx+m
  void add(int64_t k, int64_t m) {
    auto z = insert({k, m, 0}), y = z++, x = y;
    while (isect(y, z)) z = erase(z);
    if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
    while ((y = x) != begin() && (--x)->p >= y->p) isect(x, erase(y));
  }

  // Query maximum
  int64_t query(int64_t x) {
    auto l = *lower_bound(x);
    return l.k * x + l.m;
  }

 private:
  const int64_t INF = numeric_limits<int64_t>::max();

  int64_t div(int64_t a, int64_t b) { return a / b - ((a ^ b) < 0 && a % b); }

  bool isect(iterator x, iterator y) {
    if (y == end()) {
      x->p = INF;
      return false;
    }
    if (x->k == y->k)
      x->p = x->m > y->m ? INF : -INF;
    else
      x->p = div(y->m - x->m, x->k - y->k);
    return x->p >= y->p;
  }
};
