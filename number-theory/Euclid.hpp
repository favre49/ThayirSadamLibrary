#include <bits/stdc++.h>
using namespace std;

// Source: ACL
// returns a pair (g,x) such that:
// g = gcd(a,b)
// xa = g mod b
// 0 <= x < b/g;
pair<int64_t, int64_t> inv_gcd(int64_t a, int64_t b) {
  using ll = int64_t;
  a = a % b;
  if (a < 0) a += b;
  if (a == 0) return {b, 0};
  ll s = b, t = a;
  ll m0 = 0, m1 = 1;
  while (t) {
    ll u = s / t;
    s -= t * u;
    m0 -= m1 * u;
    auto tmp = s;
    s = t;
    t = tmp;
    tmp = m0;
    m0 = m1;
    m1 = tmp;
  }
  if (m0 < 0) m0 += b / s;
  return {s, m0};
}
