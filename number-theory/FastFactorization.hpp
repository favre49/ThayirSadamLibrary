#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull  = unsigned long long;

// Source: KACTL + ???
// Tested on: 1027G
// Primality and factorization for 64 bit integers, using Pollard Rho and
// Miller Rabin
// KACTL modmul has been switched with my own modmul (Testing)

ull modmul(ull a, ull b, ull m) {
  long double x; ull c; ll r;
  if (a >= m) a %= m;
  if (b >= m) b %= m;
  x = a; c = x * b / m; r = (ll)(a * b - c * m) % (ll)m;
  return r < 0 ? r + m : r;
}

ull modpow(ull b, ull e, ull mod) {
  ull ans = 1;
  for (; e; b = modmul(b, b, mod), e /= 2)
    if (e & 1) ans = modmul(ans, b, mod);
  return ans;
}

// Miller-Rabin prime check
bool isPrime(ull n) {
  if (n < 2 || n % 6 % 4 != 1) return (n | 1) == 3;
  ull A[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022},
      s = __builtin_ctzll(n-1), d = n >> s;
  for (ull a : A) {   // ^ count trailing zeroes
    ull p = modpow(a%n, d, n), i = s;
    while (p != 1 && p != n - 1 && a % n && i--)
      p = modmul(p, p, n);
    if (p != n-1 && i != s) return 0;
  }
  return 1;
}

ull pollard(ull n) {
  auto f = [n](ull x) { return modmul(x, x, n) + 1; };
  ull x = 0, y = 0, t = 30, prd = 2, i = 1, q;
  while (t++ % 40 || __gcd(prd, n) == 1) {
    if (x == y) x = ++i, y = f(x);
    if ((q = modmul(prd, max(x,y) - min(x,y), n))) prd = q;
    x = f(x), y = f(f(y));
  }
  return __gcd(prd, n);
}

// Returns an uncompressed vector of all prime factors using Pollard-Rho
vector<ull> uncompressed_factor(ull n) {
  if (n == 1) return {};
  if (isPrime(n)) return {n};
  ull x = pollard(n);
  auto l = uncompressed_factor(x), r = uncompressed_factor(n / x);
  l.insert(l.end(), r.begin(),r.end());
  return l;
}

// O(n^{1/4}) factorization using Pollard-Rho
// Returns a vector of all prime factors.
vector<pair<ull,int>> factorize(ull n) {
  auto fac = uncompressed_factor(n);
  sort(fac.begin(),fac.end());
  vector<pair<ull,int>> ret;
  for (auto x : fac) {
    if (ret.empty() || ret.back().first != x)
      ret.push_back({x,1});
    else 
      ret.back().second++;
  }
  return ret;
}

