#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const ll INF = 1e18;
struct SegTreeBeats {
  struct Beat {
    ll max, smax, max_c;
    ll min, smin, min_c;
    ll sum;
    ll len, ladd, lval;
    Beat() {
      max = smax = -INF;
      min = smin = lval = INF;
      max_c = min_c = ladd = sum = len = 0;
    }
  };
  int n, sz;
  vector<Beat> beats;

  void update_node_max(int k, ll x) {
    beats[k].sum += (x - beats[k].max) * beats[k].max_c;
    if (beats[k].max == beats[k].min) beats[k].max = beats[k].min = x;
    else if (beats[k].max == beats[k].smin) beats[k].max = beats[k].smin = x;
    else beats[k].max = x;
    if (beats[k].lval != INF && x < beats[k].lval)
      beats[k].lval = x;
  }
  void update_node_min(int k, ll x) {
    beats[k].sum += (x - beats[k].min) * beats[k].min_c;
    if (beats[k].max == beats[k].min) beats[k].max = beats[k].min = x;
    else if (beats[k].smax == beats[k].min) beats[k].smax = beats[k].min = x;
    else beats[k].min = x;
    if (beats[k].lval != INF && beats[k].lval < x)
      beats[k].lval = x;
  }
  void update(int k){
    beats[k].sum = beats[2*k+1].sum + beats[2*k+2].sum;
    if (beats[2*k+1].max < beats[2*k+2].max) {
      beats[k].max = beats[2*k+2].max;
      beats[k].max_c = beats[2*k+2].max_c;
      beats[k].smax = max(beats[2*k+1].max, beats[2*k+2].smax);
    }
    else if (beats[2*k+1].max > beats[2*k+2].max) {
      beats[k].max = beats[2*k+1].max;
      beats[k].max_c = beats[2*k+1].max_c;
      beats[k].smax = max(beats[2*k+1].smax, beats[2*k+2].max);
    }
    else {
      beats[k].max = beats[2*k+1].max;
      beats[k].max_c = beats[2*k+1].max_c + beats[2*k+2].max_c;
      beats[k].smax = max(beats[2*k+1].smax, beats[2*k+2].smax);
    }
    if (beats[2*k+1].min < beats[2*k+2].min) {
      beats[k].min = beats[2*k+1].min;
      beats[k].min_c = beats[2*k+1].min_c;
      beats[k].smin = min(beats[2*k+1].smin, beats[2*k+2].min);
    }
    else if (beats[2*k+1].min > beats[2*k+2].min) {
      beats[k].min = beats[2*k+2].min;
      beats[k].min_c = beats[2*k+2].min_c;
      beats[k].smin = min(beats[2*k+1].min, beats[2*k+2].smin);
    }
    else {
      beats[k].min = beats[2*k+1].min;
      beats[k].min_c = beats[2*k+1].min_c + beats[2*k+2].min_c;
      beats[k].smin = min(beats[2*k+1].smin, beats[2*k+2].smin);
    }
  }
  void addall(int k, ll x) {
    beats[k].max += x;
    if (beats[k].smax != -INF) beats[k].smax += x;
    beats[k].min += x;
    if (beats[k].smin != INF) beats[k].smin += x;
    beats[k].sum += beats[k].len * x;
    if (beats[k].lval != INF) beats[k].lval += x;
    else beats[k].ladd += x;
  }
  void updateall(int k, ll x) {
    beats[k].max = x; beats[k].smax = -INF;
    beats[k].min = x; beats[k].smin = INF;
    beats[k].max_c = beats[k].min_c = beats[k].len;
    beats[k].sum = x*beats[k].len;
    beats[k].lval = x;
    beats[k].ladd = 0;
  }
  void push(int k) {
    if (sz - 1 <= k) return;
    if (beats[k].lval != INF) {
      updateall(2*k+1, beats[k].lval);
      updateall(2*k+2, beats[k].lval);
      beats[k].lval = INF;
      return;
    }
    if (beats[k].ladd != 0) {
      addall(2*k+1, beats[k].ladd);
      addall(2*k+2, beats[k].ladd);
      beats[k].ladd = 0;
    }
    if (beats[k].max < beats[2*k+1].max) update_node_max(2*k+1,beats[k].max);
    if (beats[k].min > beats[2*k+1].min) update_node_min(2*k+1,beats[k].min);
    if (beats[k].max < beats[2*k+2].max) update_node_max(2*k+2,beats[k].max);
    if (beats[k].min > beats[2*k+2].min) update_node_min(2*k+2,beats[k].min);
  }
  void _update_min(ll x, int a, int b, int k, int l, int r) {
    if (b <= l || r <= a || beats[k].max <= x) return;
    if (a <= l && r <= b && beats[k].smax < x) {
      update_node_max(k, x);
      return;
    }
    push(k);
    _update_min(x, a, b, 2 * k + 1, l, (l + r) / 2);
    _update_min(x, a, b, 2 * k + 2, (l + r) / 2, r);
    update(k);
  }
  void _update_max(ll x, int a, int b, int k, int l, int r) {
    if (b <= l || r <= a || x <= beats[k].min) return;
    if (a <= l && r <= b && x < beats[k].smin) {
      update_node_min(k, x);
      return;
    }
    push(k);
    _update_max(x, a, b, 2 * k + 1, l, (l + r) / 2);
    _update_max(x, a, b, 2 * k + 2, (l + r) / 2, r);
    update(k);
  }
  void _add_val(ll x, int a, int b, int k, int l, int r) {
    if (b <= l || r <= a) return;
    if (a <= l && r <= b) {
      addall(k, x);
      return;
    }
    push(k);
    _add_val(x, a, b, 2 * k + 1, l, (l + r) / 2);
    _add_val(x, a, b, 2 * k + 2, (l + r) / 2, r);
    update(k);
  }
  void _update_val(ll x, int a, int b, int k, int l, int r) {
    if (b <= l || r <= a) return;
    if (a <= l && r <= b) {
      updateall(k, x);
      return;
    }
    push(k);
    _update_val(x, a, b, 2 * k + 1, l, (l + r) / 2);
    _update_val(x, a, b, 2 * k + 2, (l + r) / 2, r);
    update(k);
  }

  ll _query_max(int a, int b, int k, int l, int r) {
    if (b <= l || r <= a) return -INF;
    if (a <= l && r <= b) return beats[k].max;
    push(k);
    ll lv = _query_max(a, b, 2 * k + 1, l, (l + r) / 2);
    ll rv = _query_max(a, b, 2 * k + 2, (l + r) / 2, r);
    return max(lv, rv);
  }

  ll _query_min(int a, int b, int k, int l, int r) {
    if (b <= l || r <= a) return INF;
    if (a <= l && r <= b) return beats[k].min;
    push(k);
    ll lv = _query_min(a, b, 2 * k + 1, l, (l + r) / 2);
    ll rv = _query_min(a, b, 2 * k + 2, (l + r) / 2, r);
    return min(lv, rv);
  }

  ll _query_sum(int a, int b, int k, int l, int r) {
    if (b <= l || r <= a) return 0;
    if (a <= l && r <= b) return beats[k].sum;
    push(k);
    ll lv = _query_sum(a, b, 2 * k + 1, l, (l + r) / 2);
    ll rv = _query_sum(a, b, 2 * k + 2, (l + r) / 2, r);
    return lv + rv;
  }

  SegTreeBeats(int _n):SegTreeBeats(vector<ll>(_n)) {}
  SegTreeBeats(const vector<ll>& a):n(a.size()) {
    sz = 1;
    while(sz < n) sz <<= 1;
    beats.resize(2*sz);
    beats[0].len = sz;
    for (int i = 0; i < sz-1; i++)
      beats[2*i+1].len = beats[2*i+2].len = (beats[i].len>>1);
    for (int i = 0; i < n; i++){
      int j = sz-1+i;
      beats[j].max = beats[j].min = beats[j].sum = a[i];
      beats[j].smax = -INF;
      beats[j].smin = INF;
      beats[j].max_c = beats[j].min_c = 1;
    }
    for (int i = sz-2; i >= 0; i--)
      update(i);
  }

  // all queries are performed on [l, r) segment

  // range minimize query
  void update_min(int a, int b, ll x) {
    _update_min(x, a, b, 0, 0, sz);
  }
  // range maximize query
  void update_max(int a, int b, ll x) {
    _update_max(x, a, b, 0, 0, sz);
  }
  // range add query
  void add_val(int a, int b, ll x) {
    _add_val(x, a, b, 0, 0, sz);
  }
  // range update query
  void update_val(int a, int b, ll x) {
    _update_val(x, a, b, 0, 0, sz);
  }
  // range minimum query
  ll query_max(int a, int b) {
    return _query_max(a, b, 0, 0, sz);
  }
  // range maximum query
  ll query_min(int a, int b) {
    return _query_min(a, b, 0, 0, sz);
  }
  // range sum query
  ll query_sum(int a, int b) {
    return _query_sum(a, b, 0, 0, sz);
  }
};
