#include <bits/stdc++.h>
using namespace std;

// Source: Nyaan, with changes
// Tested on: ABC 217 H
// Fast handling of convex piecewise linear functions
// Add convex function, get min, sliding window min, etc.
// If you want f(0) = 0, f(x) = INF (for x != 0), then just add 0 ~2*n times
struct SlopeTrick {
  using ll = int64_t;
  const ll INF = 1e16;
  ll mn;
  ll addL, addR;
  priority_queue<ll> L;
  priority_queue<ll,vector<ll>,greater<ll>> R;

  SlopeTrick() : mn(0), addL(0), addR(0) {}

  // Helper functions
  void pushL(ll x) { L.push(x - addL); }
  void pushR(ll x) { R.push(x - addR); }
  ll getL() { 
    if (L.empty()) return -INF;
    return L.top() + addL; 
  }
  ll getR() { 
    if (R.empty()) return INF;
    return R.top() + addR; 
  }
  void popL() { L.pop(); }
  void popR() { R.pop(); }

  // Shift set of convex functions
  void shiftL(ll a) { addL += a; }
  void shiftR(ll a) { addR += a; }
  void shiftX(ll a) { addL += a, addR += a; } // f(x) <- f(x-a)
  void shiftY(ll a) { mn += a; } // f(x) <- f(x)+a

  // Get minimum value
  ll get_min() { return mn; }

  // Get samllest x at which minimum value occurs. Generally happens in range
  // from [l0,r0]
  ll get_min_x() { return L.empty()?R.empty()?0:getR():getL(); }

  // Add (x-a)_+ ____/ [max(x-a,0)]
  void add_xma(ll a) {
    mn += max(ll(0),getL()-a);
    pushL(a);
    pushR(getL());
    popL();
  }

  // add (a-x)_+ \_____  [max(a-x,0)]
  void add_amx(ll a) {
    mn += max(ll(0),a-getR());
    pushR(a);
    pushL(getR());
    popR();
  }

  // add |x-a| \___/
  void add_abs_xma(ll a) {
    add_xma(a);
    add_amx(a);
  }

  // g(x) = min(y<x) f(y), \_/ -> \__
  void cum_min_right() { decltype(R){}.swap(R); }

  // g(x) = min(y>x) f(y), \_/ -> __/
  void cum_min_left() { decltype(L){}.swap(L); }

  // Sliding window minimum, i.e.
  // g(x) = min f(y) (x-b <= y <= x-a)
  void sl_min(ll a, ll b) {
    addL += a;
    addR += b;
  }

  // Find f(x)
  // Destructive
  ll eval(ll x) {
    ll ret = mn;
    while(!L.empty()) {
      ret += max(ll(0),getL()-x);
      popL();
    }
    while(!R.empty()) {
      ret += max(ll(0),getR()-x);
      popR();
    }
    return ret;
  }
};
