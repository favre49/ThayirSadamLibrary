#include <bits/stdc++.h>
using namespace std;

// Source: bqi343
// Tested On: CF 1361 C
// Find Eulerian path starting at src in O(N+M).
// Returns vector of {vertex,label of edge to vertex}.
// Second element of first pair is -1.
// WARNINGS:
// 1. Check if graph is Eulerian before using this.
// 2. Ensure you've set it to directed if it's directed
struct EulerWalk {
  using pii = pair<int, int>;
  int n;
  vector<vector<pii>> g;  // the graph
  vector<vector<pii>::iterator> its;
  vector<pii> edges;  // Edges stored, indexed by label
  vector<bool> used;
  bool directed;

  EulerWalk(int _n, bool _directed = false)
      : n(_n), g(_n), its(_n), directed(_directed) {}

  void add_edge(int u, int v) {
    int m = used.size();
    used.push_back(0);
    edges.push_back({u, v});
    g[u].push_back({v, m});
    if (!directed) g[v].push_back({u, m});
  }

  vector<pii> walk(int src = 0) {
    for (int i = 0; i < n; i++) its[i] = g[i].begin();
    vector<pair<pii, int>> ret, s = {{{src, -1}, -1}};
    while (!s.empty()) {
      int x = s.back().first.first;
      auto &it = its[x], en = g[x].end();
      while (it != en && used[it->second]) it++;
      if (it == en) {
        if (!ret.empty() && ret.back().first.second != x) return {};
        ret.push_back(s.back());
        s.pop_back();
      } else {
        s.push_back({{it->first, x}, it->second});
        used[it->second] = 1;
      }
    }
    if (ret.size() != used.size() + 1) return {};
    vector<pii> ans;
    for (auto t : ret) ans.push_back({t.first.first, t.second});
    reverse(ans.begin(), ans.end());
    return ans;
  }
};
