#include <bits/stdc++.h>
using namespace std;

// Source: Nyaan
// Tested on: https://atcoder.jp/contests/abc217/tasks/abc217_h
//
// Manage a set of convex functions.
struct SlopeTrick {
  public:
    SlopeTrick() : minimum(0), addL(0), addR(0) {}

    int64_t get_minimum() { return minimum; }

    int64_t get_minimum_x() {
      return L.empty()?R.empty()?0:getR():getL();
    }

    void shiftL(int64_t a) { addL += a; }
    void shiftR(int64_t a) { addR += a; }
    void shiftX(int64_t a) { addL += a, addR += a; } // f(x) <- f(x-a)
    void shiftY(int64_t a) { minimum += a; } // f(x) <- f(x) + a

    // Add (x-a)_+ ___/ [max(x-a,0)]
    void add_xma(int64_t a) {
      minimum += max(int64_t(0), getL() - a);
      pushL(a);
      pushR(getL());
      popL();
    }

    // Add (a-x)_+ \___ [max(a-x,0)]
    void add_amx(int64_t a) {
      minimum += max(int64_t(0), a - getR());
      pushR(a);
      pushL(getR());
      popR();
    }

    // add |x-a| \___/ 
    void add_abs_xma(int64_t a) {
      add_xma(a);
      add_amx(a);
    }

    // g(x) = min(y<x) f(y), \_/ -> \__
    void cum_min_right() {
      decltype(R){}.swap(R);
    }

    // g(x) = min(y>x) f(y) , \_/ -> __/
    void cum_min_left() {
      decltype(L){}.swap(L);
    }

    // Sliding window minimum, i.e.
    // g(x) = min f(y) (x-b <= y <= x-a)
    void sl_min(int64_t a, int64_t b) {
      addL += a;
      addR += b;
    }

    int64_t eval(int64_t x) {
      int64_t ret = minimum;
      while(!L.empty()) {
        ret += max(int64_t(0),getL()-x);
        popL();
      }
      while(!R.empty()) {
        ret += max(int64_t(0),getR()-x);
        popR();
      }
      return ret;
    }

  private:
    const int64_t INF = 1e16;
    int64_t minimum;
    int64_t addL, addR;
    priority_queue<int64_t> L;
    priority_queue<int64_t, vector<int64_t>, greater<int64_t>> R;

    void pushL(int64_t x) { L.push(x - addL); }
    void pushR(int64_t x) { R.push(x - addR); }
    int64_t getL() {
      if (L.empty()) return -INF;
      return L.top() + addL;
    }
    int64_t getR() {
      if (R.empty()) return INF;
      return R.top() + addR;
    }
    void popL() { L.pop(); }
    void popR() { R.pop(); }
};
