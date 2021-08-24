#include <bits/stdc++.h>
using namespace std;

// Source: cp-algorithms
// Tested on: CF 1106 F
// Complexity: O(sqrt(m))
// Solves for x in:
// a^x \equiv b \mod m
int mod_log(int a, int b, int m) {
  a %= m, b %= m;
  int k = 1, add = 0, g;
  while((g = __gcd(a,m)) > 1) {
    if (b==k) return add;
    if (b%g) return -1;
    b /= g, m /= g, ++add;
    k = (k*1LL*a/g)%m;
  }
  int n = sqrt(m)+1, an = 1;
  for (int i = 0; i < n; i++) an = (1LL*an*a)%m;
  unordered_map<int,int> vals;
  for (int q = 0, cur = b; q <= n; q++) {
    vals[cur] = q;
    cur = (cur*1LL*a)%m;
  }
  for (int p = 1, cur = k; p <= n; p++) {
    cur = (cur*1LL*an)%m;
    if (vals.count(cur)) {
      int ans = n*p - vals[cur] + add;
      return ans;
    }
  }
  return -1;
}
