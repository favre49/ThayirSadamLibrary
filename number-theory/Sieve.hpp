#include <bits/stdc++.h>

using namespace std;
using ll = long long;

// Source: bqi343+Me
// Tested On:
// Fast prime sieve in O(NloglogN)
// Also finds the number of primes <= x
template <int N = 100007>
struct Sieve {
  bitset<N> isPrime;
  vector<int> primes, cum;
  Sieve() {
    isPrime.set();
    isPrime[0] = isPrime[1] = 0;
    for (int i = 4; i < N; i+=2) isPrime[i] = 0;
    for (int i = 3; i*i < N; i+=2)
      if (isPrime[i])
        for (int j = i*i; j < N; j += 2*i)
          isPrime[j] = 0;
    for (int i = 0; i < N; i++) {
      if (isPrime[i])
        primes.push_back(i);
      cum.push_back(primes.size());
    }
  }

  // Factorize using sieved primes
  vector<pair<ll,int>> factorize(ll x) {
    vector<pair<ll,int>> ret;
    for (auto& p : primes) {
      if (1LL*p*p > x) continue;
      if (x%p==0) {
        ret.push_back({p,0});
        while(x%p==0) {
          ret.back().second++;
          x /= p;
        }
      }
    }
    if (x >= 2) ret.push_back({x,1});
    return ret;
  }
};
