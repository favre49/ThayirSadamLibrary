#include <bits/stdc++.h>
using namespace std;

// Source: me
// Tested on: CF 1548 C
// Polynomial library
// Many improvements possible
template <typename T>
struct Polynomial : vector<T> {
  using vector<T>::vector;
  using P = Polynomial;

  P& operator+=(const P& r) {
    if (r.size() > this->size()) this->resize(r.size());
    for (int i = 0; i < (int)r.size(); i++)
      (*this)[i] += r[i];
    return *this;
  }

  P& operator+=(const T& r) {
    if (this->empty()) this->resize(1);
    (*this)[0] += r;
    return *this;
  }

  P& operator-=(const P& r) {
    if (r.size() > this->size()) this->resize(r.size());
    for (int i = 0; i < (int)r.size(); i++)
      (*this)[i] -= r[i];
    return *this;
  }

  P& operator-=(const T& r) {
    if (this->empty()) this->resize(1);
    (*this)[0] -= r;
    return *this;
  }
  
  P& operator*= (const P& r) {
    vector<T> res(this->size() + r.size()-1);
    for (int i = 0; i < this->size(); i++)
      for (int j = 0; j < r.size(); j++)
        res[i+j] += (*this)[i]*r[j];
    return *this = P(res.begin(),res.end());
  }

  P& operator*= (const T& r) {
    for (int i = 0; i < this->size(); i++) (*this)[i] *= r;
    return *this;
  }

  P& operator/= (const P& r) {
    if (this->size() < r.size()) {
      this->clear();
      return *this;
    }
    int n = this->size() - r.size() + 1;
    P f(*this), g(r);
    g.shrink();
    T coeff = 1/g.back();
    for (auto& x : g) x *= coeff;
    int deg = (int)f.size() - (int)g.size() + 1;
    int gs = g.size();
    P quo(deg);
    for (int i = deg-1; i >= 0; i--) {
      quo[i] = f[i+gs-1];
      for (int j = 0; j < gs; j++)
        f[i+j] -= quo[i] * g[j];
    }
    *this = quo*coeff;
    this->resize(n,T(0));
    return *this;
  }

  P& operator %=(const P& r) {
    *this -= *this/r*r;
    shrink();
    return *this;
  }

  P operator+(const P& r) const { return P(*this) += r; }
  P operator+(const T r) const { return P(*this) += r; }
  P operator-(const P& r) const { return P(*this) -= r; }
  P operator-(const T r) const { return P(*this) -= r; }
  P operator*(const P& r) const { return P(*this) *= r; }
  P operator*(const T r) const { return P(*this) *= r; }
  P operator/(const P& r) const { return P(*this) /= r; }
  P operator%(const P& r) const { return P(*this) %= r; }

  void shrink() {
    while (this->size() && this->back() == T(0))
      this->pop_back();
  }

  // Differentiate
  P diff() const {
    const int n = (int)this->size();
    P ret(max(0,n-1));
    for (int i = 1; i < n; i++)
      ret[i-1] = (*this)[i]*i;
    return ret;
  }

  // Integrate
  // Can make it faster by finding inverses faster
  P integral() const {
    const int n = (int)this->size();
    P ret(n+1);
    ret[0] = 0;
    for (int i = 0; i < n; i++)
      ret[i+1] = (*this)[i]/T(i+1);
    return ret;
  }

  T eval(T x) const {
    T res = 0, cum = 1;
    for (int i = 0; i < this->size(); i++) {
      res += (*this)[i]*cum;
      cum *= x;
    }
    return res;
  }
};

// Interpolate using Lagrangian interpolation
// Input in the form (x,f(x))
template<typename T> 
Polynomial<T> interpolate(vector<pair<int,T>> pts) {
  Polynomial<T> ret;
  for (int i = 0; i < (int)pts.size(); i++) {
    Polynomial<T> prod({1});
    T todiv = 1;
    for (int j = 0; j < (int)pts.size(); j++) {
      if (i==j) continue;
      todiv *= (pts[i].first-pts[j].first);
      Polynomial<T> tmp({-pts[j].first,1});
      prod *= tmp;
    }
    prod /= todiv;
    prod *= pts[i].second;
    ret += prod;
  }
  return ret;
}


