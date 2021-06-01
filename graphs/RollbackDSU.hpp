#include <bits/stdc++.h>
using namespace std;

// Source: Me
// Tested On: CF-1039-C
struct RollbackDSU {
  struct node {
    int p;
    int s;
  };
  vector<node> nodes;
  vector<pair<int,node>> q;

  RollbackDSU(int n) {
    nodes.resize(n);
    for (int i = 0; i < n; i++) {
      nodes[i].p = i, nodes[i].s = 1;
    }
  }

  int find(int v) {
    return (nodes[v].p != v?find(nodes[v].p):v);
  }
  bool merge(int a, int b){
    int fe = a, se = b;
    a = find(a), b = find(b);
    q.push_back({a,nodes[a]});
    q.push_back({b,nodes[b]});
    if (a != b) {
      if (nodes[a].s < nodes[b].s) swap(a,b);
      nodes[b].p = a;
      nodes[a].s += nodes[b].s;
      return true;
    }
    return false;
  }

  void rollback(int k) {
    while(q.size() > k) {
      nodes[q.back().first] = q.back().second;
      q.pop_back();
    }
  }

  int time() {
    return q.size();
  }
};
