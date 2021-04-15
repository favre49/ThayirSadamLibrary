#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int,int>;

struct Djikstra {
  int n;
  const long long INF = 1e16;
  vector<long long> d;
  vector<int> pred;
  vector<vector<pii>> adj;
  vector<vector<pii>> revadj;

  Djikstra(int _n):n(_n) {
    d.resize(n); pred.resize(n); adj.resize(n); revadj.resize(n);
  }
  void add_edge(int u, int v, int w) {
    adj[u].push_back({v,w}); revadj[v].push_back({u,w});
  }
  void djikstra(int s) {
    for (int i = 0; i< n; i++) pred[i] = -1, d[i] = INF; // reset
    d[s] = 0;
    priority_queue<pii,vector<pii>,greater<pii>> q;
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

