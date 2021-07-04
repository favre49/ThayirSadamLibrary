#include <bits/stdc++.h>
using namespace std;

// Source: Me
// Tested On:
template <typename T>
struct poly {
  // The coefficients of the polynomial in increasing order of degree
  vector<T> a;

  // Constructors
  poly(){}
  poly(vector<T> t):a(t) {}

  // Operations
  poly operator += (const poly& t) {
    a.resize(max(a.size(),t.a.size()));
    for (int i = 0; i< t.a.size(); i++)
      a[i] += t.a[i];
    return *this;
  }

  poly operator -= (const poly& t) {
    a.resize(max(a.size(),t.a.size()));
    for (int i = 0; i< t.a.size(); i++)
      a[i] -= t.a[i];
    return *this;
  }

  poly operator *= (const poly& t) {
    vector<T> ans(a.size()+t.a.size()-1);
    for (int i = 0; i < (int)a.size(); i++)
      for (int j = 0; j < (int)t.a.size(); j++)
        ans[i+j] += a[i]*t.a[j];
    a = ans;
    return *this;
  }

  poly operator *= (T t) {
    for (auto& x : a)
      x *= t;
    return *this;
  }

  poly operator /= (T d) {
    for (auto& x : a)
      x /= d;
    return *this;
  }

  T operator() (T x) {
    T res = 0, cum = 1;
    for (int i = 0; i < a.size(); i++) {
      res += a[i]*cum;
      cum *= x;
    }
    return res;
  }

  poly operator + (const poly& t) const {return poly(*this) += t;}
  poly operator - (const poly& t) const {return poly(*this) -= t;}
  poly operator * (const poly& t) const {return poly(*this) *= t;}
  poly operator * (const T t) const {return poly(*this) *= t;}
  poly operator / (T t) const {return poly(*this) /= t;}

  // Integrate polynomial
  poly integrate() {
    vector<T> res = {0};
    for (int i = 0; i < a.size(); i++)
      res.push_back(a[i]/T(i+1));
    return res;
  }

  // Differentiate polynomial
  poly deriv() {
    vector<T> res;
    for (int i = 1; i < a.size(); i++)
      res.push_back(a[i]*T(i));
    return res;
  }

  // Integrate polynomial over [l,r]
  T integrate_val(int l, int r) {
    poly ans = integrate();
    return ans(r)-ans(l);
  }

  // Interpolate using Lagrangian interpolation
  void interpolate(vector<pair<int,T>> pts) {
    poly<T> ret;
    for (int i = 0; i < (int)pts.size(); i++) {
      poly<T> prod({1});
      T todiv = 1;
      for (int j = 0; j < (int)pts.size(); j++) {
        if (i == j) continue;
        todiv *= (pts[i].first - pts[j].first);
        vector<T> tmpv({-pts[j].first,1});
        poly<T> tmp(tmpv);
        prod *= tmp;
      }
      prod /= todiv;
      prod *= pts[i].second;
      ret += prod;
    }
    *this = ret;
  }
};
