#include <bits/stdc++.h>
using namespace std;

// Source : neal
// Tested on : Yosupo Strongly Connected Components
// Components are always in reverse topological order
struct SCC {
  // Graph data
  int n;
  vector<vector<int>> adj;

  // Tarjan necessities
  vector<int> st;
  vector<bool> in_st;
  int st_sz = 0, tour;
  vector<int> tour_index, low_link;

  // Component information
  vector<vector<int>> components;
  vector<int> which_component;

  SCC(int _n):n(_n) {
    adj.resize(n);
  }
  SCC(vector<vector<int>>& _adj):n(_adj.size()), adj(_adj) {}

  void add_edge(int u, int v) { adj[u].push_back(v); }

  void tarjan(int v) {
    tour_index[v] = tour++;
    low_link[v] = tour_index[v];
    st[st_sz++] = v;
    in_st[v] = true;

    for (int u : adj[v]){
      if (tour_index[u] < 0) {
        tarjan(u);
        low_link[v] = min(low_link[v], low_link[u]);
      } else if (in_st[u]) {
        low_link[v] = min(low_link[v], tour_index[u]);
      }
    }

    if (low_link[v] == tour_index[v]) {
      components.emplace_back();
      vector<int>& component = components.back();
      int x;
      do {
        x = st[--st_sz];
        in_st[x] = false;
        which_component[x] = (int)components.size()-1;
        component.push_back(x);
      } while(x != v);
    }
  }

  void build() {
    tour_index.assign(n,-1);
    low_link.assign(n,-1);
    which_component.assign(n,-1);

    st_sz = 0;
    st.resize(n);
    in_st.resize(n);
    tour = 0;

    for (int i = 0; i < n; i++){
      if (tour_index[i] < 0)
        tarjan(i);
    }
  }
};

