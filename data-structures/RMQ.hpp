#include <bits/stdc++.h>
using namespace std;

// Source: neal
// Tested on: ???
// Queries minimum on range [l,r]
template <typename T, bool maximum_mode = false>
struct RMQ {
 public:
  RMQ() = default;
  RMQ(const vector<T>& values) : n(values.size()), values(values) {
    int levels = largest_bit(n) + 1;
    range_low.resize(levels);

    for (int k = 0; k < levels; k++) range_low[k].resize(n - (1 << k) + 1);

    for (int i = 0; i < n; i++) range_low[0][i] = i;

    for (int k = 1; k < levels; k++)
      for (int i = 0; i + (1 << k) <= n; i++)
        range_low[k][i] = better_index(range_low[k - 1][i],
                                       range_low[k - 1][i + (1 << (k - 1))]);
  }

  // Note: breaks ties by choosing the largest index.
  int query_index(int a, int b) const {
    assert(0 <= a && a <= b && b < n);
    int level = largest_bit(b - a + 1);
    return better_index(range_low[level][a],
                        range_low[level][b - (1 << level) + 1]);
  }

  T query_value(int a, int b) const { return values[query_index(a, b)]; }

 private:
  size_t n;
  vector<T> values;
  vector<vector<int>> range_low;

  int largest_bit(int x) const { return x == 0 ? -1 : 31 - __builtin_clz(x); }

  // Note: when a==b, returns b.
  int better_index(int a, int b) const {
    return (maximum_mode ? values[b] < values[a] : values[a] < values[b]) ? a
                                                                          : b;
  }
};
