#include <bits/stdc++.h>
using namespace std;

// Source: koosaga, molamola.
// Tested On: CF-102920-F, Yosupo Dominator Tree
// Dominator Tree, a directed tree with root S with edges from the immediate
// dominator to the vertex.
// Dominator = necessary vertex to get from S to v
// Uses 1-indexed values
struct DominatorTree {
  int n; // Size of arrays, number of vertices + 1
  int timer; // DFS timer
  vector<vector<int>> adj; // Adjacency list
  vector<vector<int>> radj; // Reverse adjacency list on labels
  vector<vector<int>> rdom;
  vector<int> s, rs; // new labels depending on timer and inverse
  vector<int> par, val;
  vector<int> sdom; // Label of semi dominator
  vector<int> dom; // Label of immediate dominator
  vector<int> rp;
  vector<int> up; // Points to the immediate dominator. If up[i] = S, no required vertex. If up[i] = 0, unreachable

  // _n is the number of vertices, n is the size of the arrays.
  DominatorTree(int _n):n(_n+1),timer(0),adj(n), radj(n), rdom(n), s(n), rs(n), par(n),
      val(n), sdom(n), dom(n), rp(n), up(n)
  {}

  void add_edge(int u, int v) { adj[u].push_back(v); }
  void unite(int u, int v) { par[u] = v; }
  int find(int x, int c = 0) {
    if (par[x] == x) return c? -1 : x;
    int p = find(par[x],1);
    if (p == -1) return c ? par[x] : val[x];
    if (sdom[val[x]] > sdom[val[par[x]]]) val[x] = val[par[x]];
    par[x] = p;
    return c ? p : val[x];
  }

  void dfs(int x) {
    rs[s[x] = ++timer] = x;
    par[timer] = sdom[timer] = val[timer] = timer;
    for (int v : adj[x]) {
      if (s[v] == 0)  dfs(v), rp[s[v]] = s[x];
      radj[s[v]].push_back(s[x]);
    }
  }

  int build(int s) {
    dfs(s);
    for (int i = timer; i ; i--) {
      for (int u : radj[i]) sdom[i] = min(sdom[i], sdom[find(u)]);
      if (i > 1) rdom[sdom[i]].push_back(i);
      for (int u : rdom[i]) {
        int p = find(u);
        if (sdom[p] == i) dom[u] = i;
        else dom[u] = p;
      }
      if (i > 1) unite(i,rp[i]);
    }
    for (int i = 2; i <= timer; i++) if (sdom[i] != dom[i]) dom[i] = dom[dom[i]];
    for (int i = 2; i <= timer; i++) up[rs[i]] = rs[dom[i]];
    return timer;
  }
};
