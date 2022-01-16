#include <vector>
using namespace std;

#include "../number-theory/ModInt.hpp"

// Source: Based on neal's choose implementation
// Tested on: ABC 235 G
namespace internal_choose {
  vector<mod_int> factorial = {1}, inv_factorial = {1};
  int built_max = 0;

  void prepare_factorials(int max) {
    if (max <= built_max) return;
    max += max/100;
    factorial.resize(max+1);
    inv_factorial.resize(max+1);
    for (int i = built_max+1; i <= max; i++)
      factorial[i] = i*factorial[i-1];
    inv_factorial[max] = factorial[max].inv();
    for (int i = max-1; i > built_max; i--)
      inv_factorial[i] = inv_factorial[i+1]*(i+1);
    built_max = max;
  }
};

mod_int factorial(int n) {
  if (n < 0) return 0;
  internal_choose::prepare_factorials(n);
  return internal_choose::factorial[n];
}

mod_int inv_factorial(int n) {
  if (n < 0) return 0;
  internal_choose::prepare_factorials(n);
  return internal_choose::inv_factorial[n];
}

mod_int choose(int n, int r) {
  if (r < 0 || r > n) return 0;
  internal_choose::prepare_factorials(n);
  return internal_choose::factorial[n] * internal_choose::inv_factorial[n-r] *
    internal_choose::inv_factorial[r];
}

mod_int permute(int n, int r) {
  if (r < 0 || r > n) return 0;
  internal_choose::prepare_factorials(n);
  return internal_choose::factorial[n] * internal_choose::inv_factorial[n-r];
}

mod_int inv_choose(int n, int r) {
  assert (r >= 0 && r <= n);
  internal_choose::prepare_factorials(n);
  return internal_choose::inv_factorial[n] * internal_choose::factorial[n-r] *
    internal_choose::factorial[r];
}

mod_int inv_permute(int n, int r) {
  assert (r >= 0 && r <= n);
  internal_choose::prepare_factorials(n);
  return internal_choose::inv_factorial[n] * internal_choose::factorial[n-r];
}

