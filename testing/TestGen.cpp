#include "bits/stdc++.h"
#include "jngen.hpp"

using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

// Note: only works with integral
template<typename T>
void randomIntegerArray(int N) {
  uniform_int_distribution<T> dis;
  for (int i = 0; i < N; i++)
    cout << dis(rng) << " ";
  cout << '\n';
}

// Note: Only works with floating point numbers
// Creates numbers in the range [a,b)
template <typename T>
void randomDoubleArray(int N,int a = 0, int b = 1) {
  uniform_real_distribution<T> dis(a,b);
  for (int i =0 ; i < N; i++)
    cout << dis(rng) << " ";
  cout << '\n';
}

// Random lowercase string
void randomString(int N) {
  uniform_int_distribution<int> dis(0,25);
  for (int i =0 ; i < N; i++)
    cout << 'a' + dis(rng);
  cout << '\n';
}

int main() {
  const int T = 1; // Number of testcases
  const int N = 1e2; // Number of nodes
  const int M = 2e2; // Number of edges

  cout << T << '\n';
  for (int _ = 0; _ < T; _++) {
    // Random Tree. See jngen for structure requirements.
    //cout << Tree::random(N).shuffle().printN().add1() << '\n';
    
    // Random Graph. See jngen for structure requirements.
    //cout << Graph::random(N,M).g().printN().printM().add1() << '\n';

    // Random array.
    //cout << N << '\n';
    //randomIntegerArray<int>(N);

    // Random Weighted Graph
    //auto g = Graph::random(N,M).g();
    //WeightArray W(N); // Change to M
    //uniform_int_distribution<int> dis;
    //for (int i =0 ; i < N; i++) W[i] = dis(rng);
    //g.setVertexWeights(W); // Change to setEdgeWeights
    //cout << g.printN().printM().add1() << '\n';
  }
}
