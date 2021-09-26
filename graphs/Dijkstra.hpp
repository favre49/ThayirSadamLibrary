#include <bits/stdc++.h>
using namespace std;

// Source : Me
// Tested on : Yosupo Shortest Path
// Use __gnu_pbds::priority_queue to get tiny speed increase
struct Dijkstra {
  using ll = int64_t;
  using dist_type = pair<ll,int>;
  int n;
  const ll INF = 1e18;
  vector<ll> d;
  vector<int> pred;
  vector<vector<pair<int,ll>>> adj;

  Dijkstra(int _n):n(_n) {
    d.resize(n); pred.resize(n); adj.resize(n);
  }
  void add_edge(int u, int v, ll w) {
    adj[u].push_back({v,w});
  }
  void dijkstra(int s) {
    for (int i = 0; i< n; i++) pred[i] = -1, d[i] = INF; // reset
    d[s] = 0;
    priority_queue<dist_type,vector<dist_type>,greater<dist_type>> q;
    q.push({0,s});
    while(!q.empty()) {
      auto [d_v,v] = q.top();
      q.pop();
      if (d[v] != d_v) continue;
      for (auto [to,len] : adj[v]) {
        if (d[v]+len < d[to]) {
          d[to] = d[v]+len;
          pred[to] = v;
          q.push({d[to],to});
        }
      }
    }
  }
};

