#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// Source: Me
// Elementary number theory functions, like:
// 1. Prime factorization
// 2. Euler's totient function
// 3. Mobius function
// 4. Binary exponentiation 
// 5. Primitive roots
vector<pair<ll,int>> factorize(ll x) {
  vector<pair<ll,int>> res;
  for (ll i = 2; i*i <= x; i++) {
    if (x%i==0) {
      int c = 0;
      while(x%i==0) {
        x /= i;
        c++;
      }
      res.push_back({i,c});
    }
  }
  if (x != 1) res.push_back({x,1});
  return res;
}

// Mobius function for [1,N]
vector<int> MobiusFunction(int N) {
  vector<int> mu(N+1), lpf(N+1);
  mu[1] = 1;
  for (int i = 2; i <= N; i++) {
    if (!lpf[i]) {
      for (int j = i; j <= N; j += i)
        lpf[j] = i;
    }
    if (lpf[i/lpf[i]] == lpf[i])
      mu[i] = 0;
    else
      mu[i] = -mu[i/lpf[i]];
  }
  return mu;
}

// Evaluate mobius function
int mu(ll x) {
  if (x==1) return 1;
  auto pf = factorize(x);
  for (auto [p,c] : pf)
    if (c >= 2) return 0;
  return pf.size()%2?-1:1;
}

// Totient function for [1,N]
vector<int> TotientFunction(int N) {
  vector<int> phi(N+1);
  for (int i = 0; i <= N; i++) phi[i] = i;
  for (int i = 2; i <= N; i++) {
    if (phi[i] == i) {
      for (int j = i; j <= N; j += i)
        phi[j] = phi[j]/i*(i-1);
    }
  }
  return phi;
}

// Evaluate totient function for given x
ll phi(ll x) {
  auto pf = factorize(x);
  ll ans = x;
  for (auto [p,_] : pf)
    ans = ans/p*(p-1);
  return ans;
}

ll modpow(ll a, ll n, ll mod) {
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
bool isPrimitiveRoot(ll r, ll mod) {
  r %= mod;
  if (r==0) return false;
  auto pf = factorize(mod-1);
  for (auto [p,c] : pf) 
    if (modpow(r,(mod-1)/p, mod) == 1)
      return false;
  return true;
}

// Get the primitive root for given mod
ll getPrimitiveRoot(ll mod) {
  if (mod == 2) return 1;
  ll ret = 1;
  while(!isPrimitiveRoot(ret,mod)) ret++;
  return ret;
}
