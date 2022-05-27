#include <bits/stdc++.h>
using namespace std;

// Source: hitonanode
// Tested on: https://atcoder.jp/contests/abc236/tasks/abc236_g
//
// Semiring where + = min, *= max. Semirings can be used in matrix
// exponentiation
template <class T>
struct min_max_semiring {
  T val;
  min_max_semiring() : val(numeric_limits<T>::max()) {}
  min_max_semiring(T x) : val(x) {}
  min_max_semiring operator+(const min_max_semiring& o) const {
    return (this->val < o.val ? this->val : o.val);
  }
  min_max_semiring& operator+=(const min_max_semiring& o) {
    return *this = *this + o;
  }
  min_max_semiring operator*(const min_max_semiring& o) const {
    return (this->val > o.val ? this->val : o.val);
  }
  min_max_semiring& operator*=(const min_max_semiring& o) {
    return *this = *this * o;
  }
  friend ostream& operator<<(ostream& os, const min_max_semiring& x) {
    return os << x.val;
  }
};
