#include <bits/stdc++.h>
using namespace std;

// Source: me
// Tested On: Yosupo Matching on Bipartite Graph
// Find the max flow through a directed graph
// works in O(V^2E)
// Run flow algorithm with the flow() function
template<typename T = int>
struct Dinic {
  // Edge u->v with capacity cap
  struct FlowEdge {
    int u,v;
    T cap, flow = 0;
    FlowEdge(int u, int v, T cap) : u(u),v(v),cap(cap) {}
  };

  const T INF = numeric_limits<T>::max();
  vector<FlowEdge> edges;
  vector<vector<int>> adj;
  int n,m = 0;
  int s,t;
  vector<int> level, ptr;
  queue<int> q;

  // Graph with n vertices, source vertex s and sink vertex t
  Dinic(int n, int s, int t) : n(n), s(s), t(t) {
    adj.resize(n); level.resize(n); ptr.resize(n);
  }
  void add_edge(int u,int v, T cap) {
    edges.push_back({u,v,cap});
    edges.push_back({v,u,0});
    adj[u].push_back(m);
    adj[v].push_back(m+1);
    m += 2;
  }
  bool bfs() {
    while(!q.empty()) {
      int u = q.front();
      q.pop();
      for (int e : adj[u]) {
        if (edges[e].cap - edges[e].flow < 1) continue;
        if (level[edges[e].v] != -1) continue;
        level[edges[e].v] = level[u]+1;
        q.push(edges[e].v);
      }
    }
    return level[t] != -1;
  }
  T dfs(int u, T pushed) {
    if (pushed == 0) return 0;
    if (u==t) return pushed;
    for (int& cid = ptr[u]; cid < (int) adj[u].size(); cid++) {
      int id = adj[u][cid];
      int v = edges[id].v;
      if (level[u]+1!=level[v]||edges[id].cap -edges[id].flow<1) continue;
      T tr = dfs(v,min(pushed,edges[id].cap-edges[id].flow));
      if (tr==0) continue;
      edges[id].flow += tr;
      edges[id^1].flow -= tr;
      return tr;
    }
    return 0;
  }
  T flow() {
    T f = 0;
    while(1) {
      fill(level.begin(),level.end(),-1);
      level[s] = 0;
      q.push(s);
      if (!bfs()) break;
      fill(ptr.begin(),ptr.end(),0);
      while(T pushed = dfs(s,INF))
        f += pushed;
    }
    return f;
  }
  vector<bool> min_cut() {
    vector<bool> res(n);
    for (int i = 0; i < n; i++)
      res[i] = (level[i] != -1);
    return res;
  }
};
