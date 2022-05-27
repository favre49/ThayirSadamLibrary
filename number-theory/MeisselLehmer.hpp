#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// Source: Me
// Tested on: Yosupo Counting Primes
// Complexity : O((n^3/4)/logn) [To Confirm]
// Counts the number of primes, works up to 1e11
// PrimeCount.hpp should be faster, but this is being kept until working of
// that function has been established.
struct MeisselLehmer {
  static const int N = 1e7 + 7;
  static const int PHILIM_N = 1e5;
  static const int PHILIM_K = 50;
  bitset<N> isPrime;
  vector<int> primes, cum;
  vector<vector<int>> dp;
  void sieve() {
    isPrime.set();
    isPrime[0] = isPrime[1] = 0;
    for (int i = 4; i < N; i += 2) isPrime[i] = 0;
    for (int i = 3; i * i < N; i += 2) {
      if (isPrime[i])
        for (int j = i * i; j < N; j += 2 * i) isPrime[j] = 0;
    }
    for (int i = 0; i < N; i++) {
      if (isPrime[i]) primes.push_back(i);
      cum.push_back(primes.size());
    }
  }
  MeisselLehmer() {
    sieve();
    dp = vector<vector<int>>(PHILIM_N, vector<int>(PHILIM_K));
    for (int n = 0; n < PHILIM_N; n++) dp[n][0] = n;
    for (int k = 1; k < PHILIM_K; k++)
      for (int n = 0; n < PHILIM_N; n++)
        dp[n][k] = dp[n][k - 1] - dp[n / primes[k - 1]][k - 1];
  }
  ll phi(ll n, int k) {
    if (n < PHILIM_N && k < PHILIM_K) return dp[n][k];
    if (k == 1) return (n + 1) >> 1;
    if (primes[k - 1] >= n) return 1;
    return phi(n, k - 1) - phi(n / primes[k - 1], k - 1);
  }
  // count number of primes <- n
  ll pi(ll n) {
    if (n < N) return cum[n];
    int b = sqrt(n), c = pi(cbrt(n)), a = pi(sqrt(b));
    b = pi(b);
    ll res = phi(n, a) + (((b + a - 2) * (b - a + 1)) >> 1);
    for (int i = a; i < b; i++) {
      ll w = n / primes[i];
      int lim = pi(sqrt(w));
      res -= pi(w);
      if (i <= c) {
        for (int j = i; j < lim; j++) {
          res += j;
          res -= pi(w / primes[j]);
        }
      }
    }
    return res;
  }
};
