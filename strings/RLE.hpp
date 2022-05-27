#include <bits/stdc++.h>
using namespace std;

// Source: ???
// Find the run length encoding of a string or array
template <typename T = char, typename U>
vector<pair<T, int>> run_length_encoding(const U& s) {
  int n = s.size();
  vector<pair<T, int>> res;
  if (n == 0) return res;
  T st = s.front();
  int cnt = 1;
  for (int i = 1; i < n; i++) {
    if (s[i] != st) {
      res.push_back({st, cnt});
      cnt = 0;
    }
    st = s[i];
    cnt++;
  }
  res.push_back({st, cnt});
  return res;
}
