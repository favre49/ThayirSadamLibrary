#include <bits/stdc++.h>
using namespace std;

#include "Point.hpp"

// Implementations from KACTL, untested
template<class T>
struct TCircle {
  typedef TCircle C;
  typedef TPoint<T> P;
  static constexpr T eps = static_cast<T>(1e-9);
  static constexpr T PI = atan(1)*4;
  P c;
  T r;
  TCircle(T x, T y, T rad):c(x,y),r(rad) {}
  TCircle(P c, T rad):c(c),r(rad) {}
  T area() const { return PI*r*r; }
  T perimeter() const { return 2*PI*r; }
  T diameter() const { return 2*r; }

  // Returns true if there is an intersection
  bool intersect(C& other, pair<P,P>& out) {
    P delta = other.c-c;
    assert(delta.x || delta.y || r != other.r);
    if (!delta.x && !delta.y) return false;
    T rt = r+other.r, d2 = delta.dist2();
    T p = (d2+r*r-other.r*other.r)/(2.0*d2);
    T h2 = r*r-p*p*d2;
    if (d2 > rt*rt || h2 < 0) return false;
    P mid = c+delta*p,per = delta.perp()*sqrt(h2/d2);
    out = {mid+per,mid-per};
    return true;
  }

  // Returns a pair of two points on the circle whos tangents intersect at p
  // If p is inside the circle, NAN.
  // First point is the one to the right as seen from p towards the center
  pair<P,P> circleTangents(const P &p) {
    P a = p - c;
    T x = r*r/a.dist2(), y = sqrt(x-x*x);
    return make_pair(c+a*x+a.perp()*y,c+a*x-a.perp()*y);
  }
};

using Circle = TCircle<long double>;

