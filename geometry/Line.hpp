#include <bits/stdc++.h>

#include "Point.hpp"
using namespace std;

template <class T>
struct TLine {
  typedef TLine L;
  typedef TPoint<T> P;
  static constexpr T eps = static_cast<T>(1e-9);
  P a, b, ab;
  TLine() : a(), b(), ab() {}
  TLine(const P& a, const P& b, bool twoPoints = true)
      : a(a), b(b), ab(twoPoints ? b - a : b) {}
  TLine(const T& xa, const T& ya, const T& xb, const T& yb)
      : a(xa, ya), b(xb, yb), ab(xb - xa, yb - ya) {}
  bool onLine(const P& p) {
    if (a == b) return p == a;
    return abs((p - a).cross(ab)) <= eps;
  }
  bool onSeg(const P& p) const {
    if (a == b) return p == a;
    auto veca = a - p, vecb = b - p;
    return abs(veca.cross(vecb)) <= eps && veca.dot(vecb) <= eps;
  }
  T distLine(const P& p) {
    if (a == b) return (a - p).dist();
    return abs((p - a).cross(ab)) / ab.dist();
  }
  T distSeg(const P& p) {
    if ((p - a).dot(ab) <= 0) return (p - a).dist();
    if ((p - b).dot(ab) >= 0) return (p - b).dist();
    return distLine(p);
  }
  P projection(const P& p) {
    P res = a;
    if (a == b) return a;
    res = res + ab * ((p - a).dot(ab) / ab.dist2());
    return res;
  }
  P reflection(const P& p) {
    P res = projection(p);
    res = res * 2 - p;
    return res;
  }

  // Returns 0 if parallel or collinear
  // returns 1 if unique intersections
  // returns -1 if infinite intersections
  int intersect(const L& l, P& res) const {
    if (abs(ab.cross(l.ab)) > eps) {  // not parallel
      res = l.a - (l.ab) * ab.cross(l.a - a) / (ab).cross(l.ab);
      return 1;
    } else
      return -(abs(ab.cross(l.a - a)) <= eps || l.a == l.b);
  }

  // returns 1 if unique, stored in r1
  // returns 2 if infinitely many, r1 and r2 are endpoints
  // returns 0 if no intersection
  vector<P> intersectSeg(const L& l) const {
    T oa = l.a.cross(l.b, a), ob = l.a.cross(l.b, b), oc = a.cross(b, l.a),
      od = a.cross(b, l.b);
    if (sgn(oa) * sgn(ob) < 0 && sgn(oc) * sgn(od) < 0)
      return {(a * ob - b * oa) / (ob - oa)};
    set<P> s;
    if (l.onSeg(a)) s.insert(a);
    if (l.onSeg(b)) s.insert(b);
    if (onSeg(l.a)) s.insert(l.a);
    if (onSeg(l.b)) s.insert(l.b);
    return {s.begin(), s.end()};
  }
};

using Line = TLine<long double>;
