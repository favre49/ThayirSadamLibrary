#include <bits/stdc++.h>
using namespace std;

// Source: neal
// Tested on: ???
template<typename T, bool maximum_mode = false>
struct RMQ {
  int n = 0;
  vector<T> values;
  vector<vector<int>> range_low;

  RMQ(const vector<T> &_values = {}) {
    if (!_values.empty())
      build(_values);
  }

  static int largest_bit(int x) {
    return x == 0 ? -1 : 31 - __builtin_clz(x);
  }

  // Note: when equal, returns b.
  int better_index(int a, int b) const {
    return (maximum_mode ? values[b] < values[a] : values[a] < values[b]) ? a : b;
  }

  void build(const vector<T> &_values) {
    values = _values;
    n = int(values.size());
    int levels = largest_bit(n) + 1;
    range_low.resize(levels);

    for (int k = 0; k < levels; k++)
      range_low[k].resize(n - (1 << k) + 1);

    for (int i = 0; i < n; i++)
      range_low[0][i] = i;

    for (int k = 1; k < levels; k++)
      for (int i = 0; i <= n - (1 << k); i++)
        range_low[k][i] = better_index(range_low[k - 1][i], range_low[k - 1][i + (1 << (k - 1))]);
  }

  // Query range [a,b)
  // Note: breaks ties by choosing the largest index.
  int query_index(int a, int b) const {
    assert(0 <= a && a < b && b <= n);
    int level = largest_bit(b - a);
    return better_index(range_low[level][a], range_low[level][b - (1 << level)]);
  }

  // Query range [a,b)
  T query_value(int a, int b) const {
    return values[query_index(a, b)];
  }
};
