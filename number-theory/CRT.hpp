#include <bits/stdc++.h>
using namespace std;

#include "Euclid.hpp"

// Source: ACL
// Takes as input list of residues and mods
// If there is no solution, returns {0,0}
// Otherwise, returns (y,z) such that all solutions are x = y mod z
// Complexity : O(n log(lcm))
pair<int64_t,int64_t> crt(const vector<int64_t>& r, vector<int64_t>& m) {
  assert(r.size() == m.size());
  int n = (int)r.size();
  int64_t r0 = 0, m0 = 1;
  for (int i = 0; i < n; i++) {
    assert(1 <= m[i]);
    int64_t r1 = r[i]%m[i], m1 = m[i];
    if (r1 < 0) r1 += m[i];
    if (m0 < m1) {
      swap(r0,r1);
      swap(m0,m1);
    }
    if (m0 % m1 == 0) {
      if (r0 %m1 != r1) return {0,0};
      continue;
    }
    int64_t g, im;
    tie(g,im) = inv_gcd(m0,m1);
    int64_t u1 = m1/g;
    if ((r1-r0)%g) return {0,0};
    int64_t x = (r1-r0)/g%u1 * im%u1;
    r0 += x*m0;
    m0 *= u1;
    if (r0 < 0) r0 += m0;
  }
  return {r0,m0};
}
