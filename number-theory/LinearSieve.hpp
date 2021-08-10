#include <bits/stdc++.h>
using namespace std;

// Source: Nisiyama_Suzune
// Calculate f(x) for [1,N] where f is a multiplicative function
// Calculates f(p^k) = k
vector<int> linear_sieve(int N) {
  vector<int> f(N+1), cnt(N+1), prime;
  vector<bool> is_composite(N+1);
  f[1] = 1;
  for (int i = 2; i <= N; i++) {
    if (!is_composite[i]) { // Prime number, seed f(p)
      prime.push_back(i);
      f[i] = 1; // TODO: seed f(p)
      cnt[i] = 1;
    }
    for (int j = 0; j < prime.size() && i*prime[j] <= N; j++) {
      is_composite[i*prime[j]] = true;
      if (i%prime[j] == 0) { // p and i are not coprime
        // f(ip) = f(i/p^cnt[i]) * f(p^(cnt[i]+1))
        // f(ip) = f(i)/f(p^cnt[i]) * f(p^(cnt[i]+1)) [Denom shouldn't be 0]
        f[i*prime[j]] = f[i]/cnt[i] * (cnt[i]+1);
        break;
      }
      else { // p and i are coprime, f[ip] = f[i]*f[p]
        f[i*prime[j]] = f[i]*f[prime[j]];
        cnt[i*prime[j]] = 1;
      }
    }
  }
  return f;
}
