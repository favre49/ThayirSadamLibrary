#include <bits/stdc++.h>
using namespace std;

// Source: ACL
// Tested on: ARC111 E
// Find sum of floor((ai+b)/m), 0 <= i <= n-1
// O(log(n+m+a+b))
int64_t floor_sum(int64_t n, int64_t m, int64_t a, int64_t b) {
  int64_t ans = 0;
  if (a >= m) {
    ans += (n - 1) * n * (a / m) / 2;
    a %= m;
  }
  if (b >= m) {
    ans += n * (b / m);
    b %= m;
  }

  int64_t y_max = (a * n + b) / m, x_max = (y_max * m - b);
  if (y_max == 0) return ans;
  ans += (n - (x_max + a - 1) / a) * y_max;
  ans += floor_sum(y_max, a, m, (a - x_max % a) % a);
  return ans;
}
