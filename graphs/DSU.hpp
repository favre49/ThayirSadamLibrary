#include <bits/stdc++.h>
using namespace std;

// Source: Me
struct DSU {
  struct node {
    int p; // parent
    int s; // size
  };

  vector<node> nodes;
  DSU(int n) {
    nodes.resize(n);
    for (int i =0; i < n; i++) {
      nodes[i].p = i;
      nodes[i].s = 1;
    }
  }

  node& operator[](int index) {
    return nodes[index];
  }

  int size(int v) {
    return nodes[find(v)].s;
  }

  int find(int v) {
    if (nodes[v].p==v)
      return v;
    return nodes[v].p = find(nodes[v].p);
  }

  bool merge(int a, int b) {
    a = find(a);
    b = find(b);
    if (a==b)
      return false;
    if (nodes[a].s < nodes[b].s)
      swap(a,b);
    nodes[b].p = a;
    nodes[a].s += nodes[b].s;
    return true;
  }
};
