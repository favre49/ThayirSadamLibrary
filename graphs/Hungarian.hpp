#include <bits/stdc++.h>
using namespace std;

// Source: KACTL
// Tested on: Hackerrank Inter-Hall Courier Service
// Given a weighted bipartite graph, finds minimum weight matching.
// Takes cost[n][m], where cost[i][j] = cost for L[i] to be matched with R[j]
// returns {min cost, match} such that L[i] is matched with R[match[i]]
// Negate costs for max cost.
// Complexity is O(N^2M)
template<typename T>
pair<T,vector<int>> hungarian(const vector<vector<T>>& c) {
  if (c.empty()) return {0,{}};
  int n = c.size()+1, m = c[0].size()+1;
  vector<T> u(n), v(m);
  vector<int> p(m), ans(n-1);
  for (int i = 1; i < n; i++) {
    p[0] = i;
    int j0 = 0; // Dummy worker 0
    vector<T> dist(m,numeric_limits<T>::max());
    vector<int> pre(m,-1);
    vector<bool> done(m+1);
    do { // dijkstra
      done[j0] = 1;
      int i0 = p[j0], j1;
      T delta = numeric_limits<T>::max();
      for (int j = 1; j < m; j++) {
        if (!done[j]) {
          auto curr = c[i0-1][j-1] - u[i0] - v[j];
          if (curr < dist[j]) dist[j] = curr, pre[j] = j0;
          if (dist[j] < delta) delta = dist[j], j1 = j;
        }
      }
      for (int j = 0; j < m; j++) {
        if (done[j])
          u[p[j]] += delta, v[j] -= delta;
        else
          dist[j] -= delta;
      }
      j0 = j1;
    } while(p[j0]);
    while(j0) { // update alternating path
      int j1 = pre[j0];
      p[j0] = p[j1], j0 = j1;
    }
  }
  for (int j= 1; j < m; j++) {
    if (p[j])
      ans[p[j]-1] = j-1;
  }
  return {-v[0],ans}; // min cost
}
