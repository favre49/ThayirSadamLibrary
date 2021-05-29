#include <bits/stdc++.h>

using namespace std;

// Source: Edited version from KoD
// Tested on: Yosupo Judge Kth Smallest
// bit_vector is just a helper struct, see the WaveletMatrix part
struct bit_vector {
  using size_type = size_t;
  using bit_type = uint64_t;
  using count_type = uint32_t;
  static constexpr size_type wordsize = numeric_limits<size_type>::digits;
  size_type size;
  vector<bit_type> blocks;
  vector<count_type> accum;
  bit_vector(){}
  bit_vector(vector<bool>& a) { build(a); }

  void build(vector<bool>& a) {
    size = a.size();
    size_t fixedsize = size/wordsize+1;
    blocks.assign(fixedsize,0);
    accum.assign(fixedsize,0);
    for (size_type i = 0; i < size; i++)
      blocks[i/wordsize] |= (bit_type(a[i])&1)<<(i&(wordsize-1));
    for (size_type i = 1; i < fixedsize; i++)
      accum[i] = accum[i-1] + __builtin_popcountll(blocks[i-1]);
  }

  bool access(size_type idx) const {
    return blocks[idx/wordsize]>>(idx&(wordsize-1))&1;
  }
  size_type rank(bool value, size_t idx) const {
    bit_type mask = (bit_type(1)<<(idx&(wordsize-1)))-1;
    size_type res = accum[idx/wordsize] + __builtin_popcountll(blocks[idx/wordsize]&mask);
    return value?res:idx-res;
  }
  size_type select(bool value, size_type idx) const {
    if (idx >= rank(value,size))
      return size;
    size_type ok = 0, ng = size;
    while(ng - ok > 1) {
      size_type md = (ok+ng)>>1;
      (rank(value,md) <= idx?ok:ng) = md;
    }
    return ok;
  }
  size_type select(bool value, size_type idx, size_type l) const {
    return select(value,idx+rank(value,l));
  }
};

// Data structure capable of solving:
// rank = Number of occurrences of x in range
// quantile = kth smallest element in range
// count = number of elements >= x in range
// all in O(logn)
template <class T, size_t W = 30>
struct WaveletMatrix {
  using value_type = T;
  using size_type = size_t;
  static constexpr size_type wordsize = W;
  size_type size;
  array<bit_vector,wordsize> fid;
  array<size_type,wordsize> zero;
  WaveletMatrix() {}
  WaveletMatrix(vector<int>& a){ build(a); }
  void build(vector<int>& a) {
    size = a.size();
    vector<bool> bit(size);
    vector<value_type> curr(a.begin(),a.end());
    vector<value_type> next(size);
    for (size_t k = wordsize;k--;) {
      auto l = next.begin();
      auto r= next.rbegin();
      for (size_t i = 0; i < size; i++) {
        bit[i] = curr[i]>>k&1;
        (bit[i]?*(r++):*(l++)) = curr[i];
      }
      fid[k].build(bit);
      zero[k] = l - next.begin();
      reverse(next.rbegin(),r);
      curr.swap(next);
    }
  }

  // Number of elements = value in range [l,r)
  size_type rank(size_type l, size_type r, value_type value) const{
    for (size_type k = wordsize; k--;) {
      bool p = value>>k&1;
      l = fid[k].rank(p,l)+p*zero[k];
      r = fid[k].rank(p,r)+p*zero[k];
    }
    return r-l;
  }

  size_type select(size_type index, value_type value) const {
    array<size_type, wordsize+1> l,r;
    l[wordsize] = 0;
    r[wordsize] = size;
    for (size_type k = wordsize; k--;) {
      bool p = value>>k&1;
      l[k] = fid[k].rank(p,l[k+1]) + p*zero[k];
      r[k] = fid[k].rank(p,r[k+1]) + p*zero[k];
    }
    if (r[0] - l[0] <= index)
      return size;
    for (size_type k = 0; k < wordsize; k++) {
      bool p = value>>k&1;
      index = fid[k].select(p,index,l[k+1])-l[k+1];
    }
    return index;
  }

  value_type access(size_type index) const {
    value_type res =0;
    for (size_type k = wordsize; k--;) {
      bool p = fid[k].access(index);
      res |= value_type(p)<<k;
      index = fid[k].rank(p,index)+p*zero[k];
    }
    return res;
  }

  // Find the index-th smallest element (0-based) in range [l,r)
  value_type quantile(size_type l,size_type r,size_type index) const {
    value_type res = 0;
    for (size_type k = wordsize; k--;) {
      size_type lc = fid[k].rank(1,l);
      size_type rc = fid[k].rank(1,r);
      size_type zc = (r-l) - (rc-lc);
      bool p = (index >= zc);
      res |= value_type(p)<<k;
      if (p) {
        l = lc+zero[k];
        r = rc+zero[k];
        index -= zc;
      }
      else {
        l -= lc;
        r -= rc;
      }
    }
    return res;
  }

  // number of elements >= value in range [l,r)
  size_t count(size_type l, size_type r,value_type value) const {
    size_type res = 0;
    for (size_type k = wordsize; k--;) {
      size_type lc = fid[k].rank(1,l);
      size_type rc = fid[k].rank(1,r);
      if (value>>(k)&1) {
        l = lc + zero[k];
        r = rc + zero[k];
      }
      else {
        l -= lc;
        r -= rc;
        res += (rc-lc);
      }
    }
    return res+(r-l);
  }
};
