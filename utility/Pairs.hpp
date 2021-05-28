#include <bits/stdc++.h>
using namespace std;

template <typename U, typename V> struct pairnum {
  U u;
  V v;

  pairnum() : u(0), v(0) {}
  pairnum(long long val) : u(val), v(val) {}
  pairnum(const U& u_, const V& v_) : u(u_), v(v_) {}

  friend std::ostream& operator << (std::ostream& out, const pairnum& n) { return out << '(' << n.u << ',' << ' ' << n.v << ')'; }
  friend std::istream& operator >> (std::istream& in, pairnum& n) { long long val; in >> val; n = pairnum(val); return in; }

  friend bool operator == (const pairnum& a, const pairnum& b) { return a.u == b.u && a.v == b.v; }
  friend bool operator != (const pairnum& a, const pairnum& b) { return a.u != b.u || a.v != b.v; }
  bool operator < (const pairnum& o) const {
    if (u==o.u) return v < o.v;
    return u < o.u;
  }

  pairnum inv() const {
    return pairnum(u.inv(), v.inv());
  }
  pairnum neg() const {
    return pairnum(u.neg(), v.neg());
  }
  pairnum operator- () const {
    return pairnum(-u, -v);
  }
  pairnum operator+ () const {
    return pairnum(+u, +v);
  }

  pairnum& operator ++ () {
    ++u, ++v;
    return *this;
  }
  pairnum& operator -- () {
    --u, --v;
    return *this;
  }

  pairnum& operator += (const pairnum& o) {
    u += o.u;
    v += o.v;
    return *this;
  }
  pairnum& operator -= (const pairnum& o) {
    u -= o.u;
    v -= o.v;
    return *this;
  }
  pairnum& operator *= (const pairnum& o) {
    u *= o.u;
    v *= o.v;
    return *this;
  }
  pairnum& operator /= (const pairnum& o) {
    u /= o.u;
    v /= o.v;
    return *this;
  }

  friend pairnum operator ++ (pairnum& a, int) { pairnum r = a; ++a; return r; }
  friend pairnum operator -- (pairnum& a, int) { pairnum r = a; --a; return r; }
  friend pairnum operator + (const pairnum& a, const pairnum& b) { return pairnum(a) += b; }
  friend pairnum operator - (const pairnum& a, const pairnum& b) { return pairnum(a) -= b; }
  friend pairnum operator * (const pairnum& a, const pairnum& b) { return pairnum(a) *= b; }
  friend pairnum operator / (const pairnum& a, const pairnum& b) { return pairnum(a) /= b; }
};

