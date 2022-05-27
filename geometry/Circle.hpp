#include <bits/stdc++.h>

#include "Point.hpp"
using namespace std;

template <class T>
struct TCircle {
  typedef TCircle C;
  typedef TPoint<T> P;
  static constexpr T eps = static_cast<T>(1e-8);
  static constexpr T PI = 3.14159265358979323846;
  P c;
  T r;
  TCircle(T x, T y, T rad) : c(x, y), r(rad) {}
  TCircle(P c, T rad) : c(c), r(rad) {}
  T area() const { return PI * r * r; }
  T perimeter() const { return 2 * PI * r; }
  T diameter() const { return 2 * r; }

  // Returns true if there is an intersection
  bool intersect(C& other, pair<P, P>& out) {
    if (c == other.c) {
      assert(abs(r - other.r) > eps);
      return false;
    }
    P vec = other.c - c;
    T d2 = vec.dist2(), sum = r + other.r, dif = r - other.r,
      p = (d2 + r * r - other.r * other.r) / (d2 * 2), h2 = r * r - p * p * d2;
    if (sum * sum < d2 || dif * dif > d2) return false;
    P mid = c + vec * p, per = vec.perp() * sqrt(fmax(0, h2) / d2);
    out = {mid + per, mid - per};
    return true;
  }

  // Returns a pair of two points on the circle whos tangents intersect at p
  // If p is inside the circle, NAN.
  // First point is the one to the right as seen from p towards the center
  pair<P, P> circleTangents(const P& p) {
    P a = p - c;
    T x = r * r / a.dist2(), y = sqrt(x - x * x);
    return make_pair(c + a * x + a.perp() * y, c + a * x - a.perp() * y);
  }
};

using Circle = TCircle<double>;
