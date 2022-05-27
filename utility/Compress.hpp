#include <bits/stdc++.h>
using namespace std;

// Source: Nyaan
// Compress a set of unbounded values into the range [0, n)
template <class T>
struct Compress {
  vector<T> compress;

  Compress(const vector<T>& v) {
    compress = v;
    sort(compress.begin(), compress.end());
    compress.erase(unique(compress.begin(), compress.end()), compress.end());
  }

  int get(const T& x) const {
    return lower_bound(compress.begin(), compress.end(), x) - compress.begin();
  }
  int size() const { return compress.size(); }

  int operator()(const T& x) const { return get(x); }
  T operator[](int idx) { return compress[idx]; }
};
