#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using pii = pair<int,int>;

#include "../data-structures/RMQ.hpp"

// Source: Me
// Tested On: Yosupo Lowest Common Ancestor
// Assumes Connected Tree
struct LCA {
  int n;
  int tour_timer;
  vector<vector<int>> adj;
  RMQ<int> rmq;
  vector<int> depth, parent;
  vector<int> euler, first_occ;
  vector<int> tour_start, tour_end, tour_list;

  LCA(int _n):n(_n),adj(_n),depth(_n),parent(_n),first_occ(_n),tour_start(n),tour_end(n),tour_list(n)
  {}

  void add_edge(int u, int v) { adj[u].push_back(v); adj[v].push_back(u); }
  void dfs(int s, int p) {
    parent[s] = p;
    first_occ[s] = euler.size();
    euler.push_back(s);
    tour_list[tour_timer] = s;
    tour_start[s] = tour_timer++;
    for (int u : adj[s]) {
      if (u==p) continue;
      depth[u] = depth[s]+1;
      dfs(u,s);
      euler.push_back(s);
    }
    tour_end[s] = tour_timer;
  }
  void build(int root = 0) {
    tour_timer = 0;
    dfs(root,-1);
    assert(euler.size() == 2*n-1);
    vector<int> euler_depths;
    for (int v : euler)
      euler_depths.push_back(depth[v]);
    rmq.build(euler_depths);
  }

  // Find the lca of u and v
  int lca(int u, int v) {
    u = first_occ[u];
    v = first_occ[v];
    if (u > v) swap(u,v);
    return euler[rmq.query_index(u,v+1)];
  }
  // Is u an ancestor of v?
  bool is_ancestor(int u, int v) {
    return tour_start[u] <= tour_start[v] && tour_start[v] < tour_end[u];
  }
  // Check the distance from u to v
  int dist(int u, int v) {
    return depth[u] + depth[v] - 2*depth[lca(u,v)];
  }
  // Check if x is on the path from a to b
  int on_path(int x, int a, int b)  {
    return (is_ancestor(x,a)||is_ancestor(x,b)) && is_ancestor(lca(a,b),x);
  }

  // Smallest Tree that contains all of the given nodes
  // Untested, O(KlogK)
  vector<pii> compress_tree(vector<int> nodes) {
    if(nodes.empty()) return {};
    auto &&compare_tour = [&](int a, int b) {return tour_start[a] < tour_start[b]; };
    sort(nodes.begin(),nodes.end(),compare_tour);
    int k = nodes.size();
    for (int i = 0; i < k-1; i++)
      nodes.push_back(lca(nodes[i],nodes[i+1]));
    sort(nodes.begin()+k,nodes.end(),compare_tour);
    inplace_merge(nodes.begin(),nodes.begin()+k,nodes.end(),compare_tour);
    nodes.erase(unique(nodes.begin(),nodes.end()),nodes.end());
    vector<pii> res = {{nodes[0],-1}};
    for (int i = 1; i < nodes.size(); i++)
      res.push_back({nodes[i],lca(nodes[i],nodes[i-1])});
    return res;
  }
};

