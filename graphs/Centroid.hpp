#include <bits/stdc++.h>
using namespace std;

// Source: Me
// Complexity: O(nlogn)
// Basic template for centroid decomposition.
struct Centroid {
  int n;
  vector<vector<int>> g;
  vector<bool> done;
  vector<int> sz, par, cen, lev;

  Centroid(int _n):n(_n),g(n),done(n),sz(n),par(n,-1),cen(n),lev(n) {
  }

  void add_edge(int u, int v) {
    g[u].push_back(v);
    g[v].push_back(u);
  }

  void dfs(int s) {
    sz[s] = 1;
    for (auto& u : g[s]) {
      if (u == par[s] || done[u]) continue;
      par[u] = s;
      dfs(u);
      sz[s] += sz[u];
    }
  }

  int get_centroid(int s) {
    par[s] = -1;
    dfs(s);
    int tot = sz[s];
    while(true) {
      pair<int,int> mx = {0,0};
      for (auto& u : g[s]) {
        if (u == par[s] || done[u]) continue;
        mx = max(mx,{sz[u],u});
      }
      if (2*mx.first <= tot) return s;
      s = mx.second;
    }
    assert(false);
    return -1;
  }

  void build(int s, int centroid = -1) {
    done[s = get_centroid(s)] = 1;
    cen[s] = centroid, lev[s] = (centroid==-1?0:lev[centroid]+1);
  
    // Build necessary data structures here

    for (auto& u : g[s]) {
      if (!done[u])
        build(u,s);
    }
  }
};

