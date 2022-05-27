#include <bits/stdc++.h>
using namespace std;

// Source : bqi343
// Tested On: CF-102835-I
// Find biconnected components
// vertex_sets store the vertices in each biconnected component. If a vertex
// is contained in more than one component, it is an articulation point
// components stores the edges in each BCC. If it is of size 1, that edge is
// a bridge.
struct BCC {
  using pii = pair<int, int>;
  int n, timer;
  vector<vector<pii>> adj;
  vector<pii> edges;
  vector<vector<int>> components, vertex_sets;
  vector<int> disc, st;

  BCC(int _n) : n(_n), timer(0), adj(n), disc(n) {}
  void add_edge(int u, int v) {
    adj[u].push_back({v, (int)edges.size()});
    adj[v].push_back({u, (int)edges.size()});
    edges.push_back({u, v});
  }
  int dfs(int s, int p = -1) {
    int low = disc[s] = ++timer;
    for (auto [to, e] : adj[s]) {
      if (e != p) {
        if (!disc[to]) {
          st.push_back(e);
          int low_ = dfs(to, e);
          low = min(low, low_);
          if (disc[s] <= low_) {
            components.emplace_back();
            vector<int>& tmp = components.back();
            for (int y = -1; y != e;)
              tmp.push_back(y = st.back()), st.pop_back();
          }
        } else if (disc[to] < disc[s])  // back edge
        {
          low = min(low, disc[to]);
          st.push_back(e);
        }
      }
    }
    return low;
  }
  void build() {
    for (int i = 0; i < n; i++)
      if (!disc[i]) dfs(i);
    vector<bool> in(n);
    for (auto& c : components) {
      vertex_sets.emplace_back();
      auto add = [&](int x) {
        if (!in[x]) in[x] = 1, vertex_sets.back().push_back(x);
      };
      for (auto& e : c) add(edges[e].first), add(edges[e].second);
      for (auto& e : c) in[edges[e].first] = in[edges[e].second] = 0;
    }
  }
};
