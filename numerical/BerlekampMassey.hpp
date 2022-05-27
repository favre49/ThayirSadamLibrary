#include <bits/stdc++.h>
using namespace std;

// Source: ecnerwala
// Complexity: O(n^2)
// Given a sequence a_i, find the shortest possible linear recurrence p s.t.:
// a_i = \sum_{j=1}^m a_{i-j}p_j
template <typename num>
std::vector<num> BerlekampMassey(const std::vector<num>& s) {
  int n = int(s.size()), L = 0, m = 0;
  std::vector<num> C(n), B(n), T;
  C[0] = B[0] = 1;

  num b = 1;
  for (int i = 0; i < n; i++) {
    ++m;
    num d = s[i];
    for (int j = 1; j <= L; j++) d += C[j] * s[i - j];
    if (d == 0) continue;
    T = C;
    num coef = d / b;
    for (int j = m; j < n; j++) C[j] -= coef * B[j - m];
    if (2 * L > i) continue;
    L = i + 1 - L;
    B = T;
    b = d;
    m = 0;
  }

  C.resize(L + 1);
  C.erase(C.begin());
  for (auto& x : C) {
    x = -x;
  }
  return C;
}

// Source: ecnerwala
// Complexity: O(m^2 log k)
// Given the sequence a, and the linear recurrence p, find the kth term in the
// linear recurrence
// S = a, tr = p
// Usage:
// tr = BerlekampMassey(S)
// ans = linearRec(S,tr,k)
template <typename num>
num linearRec(const std::vector<num>& S, const std::vector<num>& tr,
              long long k) {
  int n = int(tr.size());
  assert(S.size() >= tr.size());

  auto combine = [&](std::vector<num> a, std::vector<num> b) {
    std::vector<num> res(n * 2 + 1);
    for (int i = 0; i <= n; i++)
      for (int j = 0; j <= n; j++) res[i + j] += a[i] * b[j];
    for (int i = 2 * n; i > n; --i)
      for (int j = 0; j < n; j++) res[i - 1 - j] += res[i] * tr[j];
    res.resize(n + 1);
    return res;
  };

  std::vector<num> pol(n + 1), e(pol);
  pol[0] = e[1] = 1;

  for (++k; k; k /= 2) {
    if (k % 2) pol = combine(pol, e);
    e = combine(e, e);
  }

  num res = 0;
  for (int i = 0; i < n; i++) res += pol[i + 1] * S[i];
  return res;
}
