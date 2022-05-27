#include <bits/stdc++.h>
using namespace std;

// Source: Edited version from KoD
// Tested on: Yosupo Judge Kth Smallest
// bit_vector is just a helper struct, see the WaveletMatrix part
namespace internal_wavelet_matrix {
struct bit_vector {
  static constexpr size_t wordsize = numeric_limits<size_t>::digits;
  size_t size;
  vector<uint64_t> blocks;
  vector<uint32_t> accum;
  bit_vector() {}
  bit_vector(vector<bool>& a) { build(a); }

  void build(vector<bool>& a) {
    size = a.size();
    size_t fixedsize = size / wordsize + 1;
    blocks.assign(fixedsize, 0);
    accum.assign(fixedsize, 0);
    for (size_t i = 0; i < size; i++)
      blocks[i / wordsize] |= (uint64_t(a[i]) & 1) << (i & (wordsize - 1));
    for (size_t i = 1; i < fixedsize; i++)
      accum[i] = accum[i - 1] + __builtin_popcountll(blocks[i - 1]);
  }

  bool access(size_t idx) const {
    return blocks[idx / wordsize] >> (idx & (wordsize - 1)) & 1;
  }
  size_t rank(bool value, size_t idx) const {
    uint64_t mask = (uint64_t(1) << (idx & (wordsize - 1))) - 1;
    size_t res = accum[idx / wordsize] +
                 __builtin_popcountll(blocks[idx / wordsize] & mask);
    return value ? res : idx - res;
  }
  size_t select(bool value, size_t idx) const {
    if (idx >= rank(value, size)) return size;
    size_t ok = 0, ng = size;
    while (ng - ok > 1) {
      size_t md = (ok + ng) >> 1;
      (rank(value, md) <= idx ? ok : ng) = md;
    }
    return ok;
  }
  size_t select(bool value, size_t idx, size_t l) const {
    return select(value, idx + rank(value, l));
  }
};
}  // namespace internal_wavelet_matrix

// Data structure capable of solving:
// rank = Number of occurrences of x in range
// quantile = kth smallest element in range
// count = number of elements >= x in range
// all in O(logn)
template <class T, size_t W = 30>
struct WaveletMatrix {
  static constexpr size_t wordsize = W;
  size_t size;
  array<internal_wavelet_matrix::bit_vector, wordsize> fid;
  array<size_t, wordsize> zero;
  WaveletMatrix() {}
  WaveletMatrix(vector<int>& a) { build(a); }
  void build(vector<int>& a) {
    size = a.size();
    vector<bool> bit(size);
    vector<T> curr(a.begin(), a.end());
    vector<T> next(size);
    for (size_t k = wordsize; k--;) {
      auto l = next.begin();
      auto r = next.rbegin();
      for (size_t i = 0; i < size; i++) {
        bit[i] = curr[i] >> k & 1;
        (bit[i] ? *(r++) : *(l++)) = curr[i];
      }
      fid[k].build(bit);
      zero[k] = l - next.begin();
      reverse(next.rbegin(), r);
      curr.swap(next);
    }
  }

  // Number of elements = value in range [l,r)
  size_t rank(size_t l, size_t r, T value) const {
    for (size_t k = wordsize; k--;) {
      bool p = value >> k & 1;
      l = fid[k].rank(p, l) + p * zero[k];
      r = fid[k].rank(p, r) + p * zero[k];
    }
    return r - l;
  }

  size_t select(size_t index, T value) const {
    array<size_t, wordsize + 1> l, r;
    l[wordsize] = 0;
    r[wordsize] = size;
    for (size_t k = wordsize; k--;) {
      bool p = value >> k & 1;
      l[k] = fid[k].rank(p, l[k + 1]) + p * zero[k];
      r[k] = fid[k].rank(p, r[k + 1]) + p * zero[k];
    }
    if (r[0] - l[0] <= index) return size;
    for (size_t k = 0; k < wordsize; k++) {
      bool p = value >> k & 1;
      index = fid[k].select(p, index, l[k + 1]) - l[k + 1];
    }
    return index;
  }

  T access(size_t index) const {
    T res = 0;
    for (size_t k = wordsize; k--;) {
      bool p = fid[k].access(index);
      res |= T(p) << k;
      index = fid[k].rank(p, index) + p * zero[k];
    }
    return res;
  }

  // Find the index-th smallest element (0-based) in range [l,r)
  T quantile(size_t l, size_t r, size_t index) const {
    T res = 0;
    for (size_t k = wordsize; k--;) {
      size_t lc = fid[k].rank(1, l);
      size_t rc = fid[k].rank(1, r);
      size_t zc = (r - l) - (rc - lc);
      bool p = (index >= zc);
      res |= T(p) << k;
      if (p) {
        l = lc + zero[k];
        r = rc + zero[k];
        index -= zc;
      } else {
        l -= lc;
        r -= rc;
      }
    }
    return res;
  }

  // number of elements >= value in range [l,r)
  size_t count(size_t l, size_t r, T value) const {
    size_t res = 0;
    for (size_t k = wordsize; k--;) {
      size_t lc = fid[k].rank(1, l);
      size_t rc = fid[k].rank(1, r);
      if (value >> (k)&1) {
        l = lc + zero[k];
        r = rc + zero[k];
      } else {
        l -= lc;
        r -= rc;
        res += (rc - lc);
      }
    }
    return res + (r - l);
  }
};
