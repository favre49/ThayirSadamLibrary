#include <bits/extc++.h>
using namespace std;

struct splitmix64_hash {
  static uint64_t splitmix64(uint64_t x) {
    // http://xorshift.di.unimi.it/splitmix64.c
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }

  size_t operator()(uint64_t x) const {
    static const uint64_t FIXED_RANDOM = std::chrono::steady_clock::now().time_since_epoch().count();
    return splitmix64(x + FIXED_RANDOM);
  }
};

using namespace __gnu_pbds;
template <typename K, typename V, typename Hash = splitmix64_hash>
using hash_map = gp_hash_table<K, V, Hash>;

template <typename K, typename Hash = splitmix64_hash>
using hash_set = hash_map<K, null_type, Hash>;

template<class T, class Compare = less<>>
using ordered_set = tree<T,null_type,Compare,rb_tree_tag,tree_order_statistics_node_update>;

