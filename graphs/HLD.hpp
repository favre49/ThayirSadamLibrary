#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#include "../data-structures/LazySegTree.hpp"

// Source: bqi343
// Tested On: Yosupo Vertex Add Path Sum
// Time: O(Nlog^2N)
// To set initial values, write into val
struct HLD {
  int n;
  vector<vector<int>> adj;
  vector<int> parent, root, depth, sz, pos, rpos;
  int timer;
  bool usingEdge;
  vector<ll> val;
  LazySegTree<ll> T;

  HLD(int _n, bool _usingEdge = false) : n(_n), adj(n), parent(n), root(n),
  depth(n), sz(n), pos(n), usingEdge(_usingEdge), val(n),T(n) {}

  void add_edge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  void size_dfs(int s) {
    sz[s] = 1;
    for (auto& u : adj[s]) {
      parent[u] = s;
      depth[u] = depth[s]+1;
      adj[u].erase(find(adj[u].begin(), adj[u].end(),s));
      size_dfs(u);
      sz[s] += sz[u];
      if (sz[u] > sz[adj[s][0]])
        swap(u,adj[s][0]);
    }
  }

  void hld_dfs(int s) {
    pos[s] = timer++;
    rpos.push_back(s);
    for (auto& u : adj[s]) {
      root[u] = (u == adj[s][0] ? root[s] : u);
      hld_dfs(u);
    }
  }

  // Build with specific root
  void build(int r = 0) {
    parent[r] = depth[r] = timer = 0;
    size_dfs(r);
    root[r] = r;
    hld_dfs(r);
    vector<ll> bld(n);
    for (int i = 0; i < n; i++) bld[pos[i]] = val[i];
    T = LazySegTree<ll>(bld);
  }

  // Get LCA in log time
  int lca(int u,int v) {
    for (; root[u] != root[v]; v = parent[root[v]])
      if (depth[root[u]] > depth[root[v]])
        swap(u,v);
    return depth[u] < depth[v] ? u : v;
  }

  template <class BinaryOp>
    void process_path(int u, int v, BinaryOp op) {
      for (; root[u] != root[v]; v = parent[root[v]]) {
        if (depth[root[u]] > depth[root[v]])
          swap(u,v);
        op(pos[root[v]], pos[v]);
      }
      if (depth[u] > depth[v])
        swap(u,v);
      op(pos[u] + usingEdge, pos[v]);
    }

  // Updates path from u to v
  void update(int u, int v, ll val) {
    process_path(u,v,[this,&val](int l, int r) {
        T.apply(l,r,val);
    });
  }

  // Updates subtree of u
  void update(int u, ll val) {
    T.apply(pos[u] + usingEdge, pos[u] + sz[u] - 1, val);
  }

  // Query path between u and v
  ll query(int u, int v) {
    ll res = 0;
    process_path(u,v, [this, &res](int l, int r) {
        res += T.query(l,r);
    });
    return res;
  }
};
