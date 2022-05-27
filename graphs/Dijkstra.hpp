#include <bits/stdc++.h>
using namespace std;

// Source : Me
// Tested on : Yosupo Shortest Path
// Use __gnu_pbds::priority_queue to get tiny speed increase
struct Dijkstra {
  using dist_type = pair<int64_t, int>;
  int n;
  const int64_t INF = 1e18;
  vector<int64_t> dist;
  vector<int> pred;
  vector<vector<pair<int, int64_t>>> adj;

  Dijkstra(int n) : n(n), dist(n), pred(n), adj(n) {}

  void add_edge(int u, int v, int64_t w) { adj[u].push_back({v, w}); }

  void build(int s) {
    for (int i = 0; i < n; i++)  // reset
      pred[i] = -1, dist[i] = INF;
    dist[s] = 0;
    priority_queue<dist_type, vector<dist_type>, greater<dist_type>> q;
    q.push({0, s});
    while (!q.empty()) {
      auto [d_v, v] = q.top();
      q.pop();
      if (dist[v] != d_v) continue;
      for (auto& [to, len] : adj[v]) {
        if (dist[v] + len < dist[to]) {
          dist[to] = dist[v] + len;
          pred[to] = v;
          q.push({dist[to], to});
        }
      }
    }
  }

  vector<int> path(int goal) const {
    if (dist[goal] == INF) return {};
    vector<int> ans = {goal};
    while (pred[goal] != -1) {
      goal = pred[goal];
      ans.push_back(goal);
    }
    reverse(ans.begin(), ans.end());
    return ans;
  }
};
