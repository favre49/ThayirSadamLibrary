#include <bits/stdc++.h>
using namespace std;

// Source: KACTL
// Add and remove intervals from a set of dijoint intervals, and merge
// overlapping intervals.
// Intervals are [l,r)
// Works in O(nlogn)
struct IntervalContainer : set<pair<int, int>> {
  iterator add_interval(int L, int R) {
    if (L == R) return end();
    auto it = lower_bound({L, R}), before = it;
    while (it != end() && it->first <= R) {
      R = max(R, it->second);
      before = it = erase(it);
    }
    if (it != begin() && (--it)->second >= L) {
      L = min(L, it->first);
      R = max(R, it->second);
      erase(it);
    }
    return insert(before, {L, R});
  }

  void remove_interval(int L, int R) {
    if (L == R) return;
    auto it = add_interval(L, R);
    auto r2 = it->second;
    if (it->first == L)
      erase(it);
    else
      (int&)it->second = L;
    if (R != r2) emplace(R, r2);
  }
};
