#include <bits/stdc++.h>
using namespace std;

// Source: Me
// Elementary number theory functions, like:
// 1. Prime factorization
// 2. Euler's totient function
// 3. Mobius function
// 4. Binary exponentiation
// 5. Primitive roots
vector<pair<int64_t, int>> factorize(int64_t x) {
  vector<pair<int64_t, int>> res;
  for (int64_t i = 2; i * i <= x; i++) {
    if (x % i == 0) {
      int c = 0;
      while (x % i == 0) {
        x /= i;
        c++;
      }
      res.push_back({i, c});
    }
  }
  if (x != 1) res.push_back({x, 1});
  return res;
}

// Mobius function for [1,N]
vector<int> MobiusFunction(int N) {
  vector<int> mu(N + 1), lpf(N + 1);
  mu[1] = 1;
  for (int i = 2; i <= N; i++) {
    if (!lpf[i]) {
      for (int j = i; j <= N; j += i) lpf[j] = i;
    }
    if (lpf[i / lpf[i]] == lpf[i])
      mu[i] = 0;
    else
      mu[i] = -mu[i / lpf[i]];
  }
  return mu;
}

// Evaluate mobius function
int mu(int64_t x) {
  if (x == 1) return 1;
  auto pf = factorize(x);
  for (auto [p, c] : pf)
    if (c >= 2) return 0;
  return pf.size() % 2 ? -1 : 1;
}

// Totient function for [1,N]
vector<int> TotientFunction(int N) {
  vector<int> phi(N + 1);
  for (int i = 0; i <= N; i++) phi[i] = i;
  for (int i = 2; i <= N; i++) {
    if (phi[i] == i) {
      for (int j = i; j <= N; j += i) phi[j] = phi[j] / i * (i - 1);
    }
  }
  return phi;
}

// Evaluate totient function for given x
int64_t phi(int64_t x) {
  auto pf = factorize(x);
  int64_t ans = x;
  for (auto [p, _] : pf) ans = ans / p * (p - 1);
  return ans;
}

int64_t modpow(int64_t a, int64_t n, int64_t mod) {
  a %= mod;
  long long ret = 1;
  while (n > 0) {
    if (n & 1) ret = ret * a % mod;
    a = a * a % mod;
    n >>= 1;
  }
  return ret % mod;
};

// Check if r is a primitive root
bool isPrimitiveRoot(int64_t r, int64_t mod) {
  r %= mod;
  if (r == 0) return false;
  auto pf = factorize(mod - 1);
  for (auto [p, c] : pf)
    if (modpow(r, (mod - 1) / p, mod) == 1) return false;
  return true;
}

// Get the primitive root for given mod
int64_t getPrimitiveRoot(int64_t mod) {
  if (mod == 2) return 1;
  int64_t ret = 1;
  while (!isPrimitiveRoot(ret, mod)) ret++;
  return ret;
}
