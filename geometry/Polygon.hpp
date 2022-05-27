#include <bits/stdc++.h>

#include "Line.hpp"
using namespace std;

template <class T>
struct TPolygon {
  typedef TPoint<T> P;
  typedef TLine<T> L;
  vector<P> poly;

  TPolygon() {}
  TPolygon(vector<P>& _poly) : poly(_poly) {}
  TPolygon(THull<T>& h) : poly(h.hull) {}

  // Returns twice the signed area
  // Clockwise enumeration gives negative area
  T area() {
    T a = poly.back().cross(poly[0]);
    for (int i = 0; i < poly.size() - 1; i++) a += poly[i].cross(poly[i + 1]);
    return a;
  }

  P center() {
    P res(0, 0);
    double A = 0;
    for (int i = 0, j = poly.size() - 1; i < poly.size(); j = i++) {
      res = res + (poly[i] + poly[j]) * poly[j].cross(poly[i]);
      A += poly[j].cross(poly[i]);
    }
    return res / A / 3;
  }

  // O(n)
  // strict = true if it returns false for points on the boundary
  bool inPolygon(vector<P>& p, P a, bool strict = true) {
    int cnt = 0, n = p.size();
    for (int i = 0; i < n; i++) {
      P q = p[(i + 1) % n];
      if (L(p[i], q).onSeg(a)) return !strict;
      cnt ^= ((a.y < p[i].y) - (a.y < q.y)) * a.cross(p[i], q) > 0;
    }
    return cnt;
  }
};
