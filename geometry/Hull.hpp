#include <bits/stdc++.h>
using namespace std;

#include "Line.hpp"

template<class P>
int sideOf(P s, P e, P p) { return sgn(s.cross(e, p)); }

// Convex hull, such that all the points are in ccw order. Points on the convex
// hull edges are not included.
template<class T>
struct THull {
  typedef TPoint<T> P;
  typedef TLine<T> L;
  vector<P> hull;

  // O(nlogn)
  THull(vector<P> pts)  {
    if (pts.size() == 1) {
      hull = pts;
      return;
    }
    sort(pts.begin(),pts.end());
    vector<P> h(pts.size()+1);
    int s = 0, t = 0;
    for (int it = 2; it--; s = --t, reverse(pts.begin(),pts.end())) {
      for (P p : pts) {
        while(t >= s + 2 && h[t-2].cross(h[t-1],p) <= 0) t--;
        h[t++] = p;
      }
    }
    hull = vector<P>(h.begin(),h.begin() + t - (t==2 && h[0] == h[1]));
  }

  // O(logn)
  // strict = true means that points on the boundary are not included
  // Untested
  bool inHull(P p, bool strict = true) {
    int a = 1, b = (int)hull.size() - 1, r = !strict;
    if ((int)hull.size() < 3)
      return r && L(hull[0],hull.back()).onSeg(p);
    if (sideOf(hull[0], hull[a],hull[b]) > 0) swap(a,b);
    if (sideOf(hull[0],hull[a],p) >= r || sideOf(hull[0],hull[b],p) <= r)
      return false;
    while(abs(a-b) > 1) {
      int c = (a+b)/2;
      (sideOf(hull[0],hull[c],p) > 0 ? b : a ) = c;
    }
    return sgn(hull[a].cross(hull[b],p)) < r;
  }

  // Find two most distant points
  array<P,2> diameter(vector<P> S) {
    int n = S.size(), j = n < 2 ? 0 : 1;
    pair<ll,array<P,2>> res({0,{S[0],S[0]}});
    for (int i = 0; i < j; i++) {
      for (;;j = (j+1)%n) {
        res = max(res,{(S[i]-S[j]).dist2(), {S[i]-S[j]}});
        if ((S[(j+1)%n] - S[j]).cross(S[i+1] - S[i]) >= 0)
          break;
      }
    }
    return res.second;
  }
};
