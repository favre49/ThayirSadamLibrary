#include <bits/stdc++.h>
using namespace std;

const int N = 1e6+7;
vector<int> prime;
bool is_composite[N];
int f[N], cnt[N];

// Calculate a multiplicative function in O(n) time
void linear_sieve(int n) {
  f[1] = 1;
  for (int i = 2; i < n; i++) {
    if (!is_composite[i]) { // Prime number, seed f(p)
      prime.push_back(i);
      f[i] = 1; // TODO: Seed initial value for prime
      cnt[i] = 1;
    }
    for (int j = 0; j < prime.size() && i*prime[j] < n; j++) {
      is_composite[i*prime[j]] = true;
      if (i%prime[j]==0)  { // p and i are not coprime
        cnt[i*prime[j]] = cnt[i]+1;
        // f(ip) = f(i / p^cnt[i]) * f(p^(cnt[i]+1))
        // f(ip) = f(i) / f(p^cnt[i]) * f(p^(cnt[i]+1)) [As long as f(p^cnt[i]) != 0
        f[i*prime[j]] = f[i]/cnt[i] * (cnt[i]+1);
        break;
      }
      else { // p and i are corpime, f[ip] = f[i] * f[p]
        f[i*prime[j]] = f[i]*f[prime[j]];
        cnt[i*prime[j]] = 1;
      }
    }
  }
}
