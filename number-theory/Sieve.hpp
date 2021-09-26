#include <bits/stdc++.h>
using namespace std;

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
};
