#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// Source: Nyaan
// Tested On:
// Matrix library
// Use M^k to raise to a power
template<class T>
struct Matrix{
  vector<vector<T>> A;

  Matrix() = default;
  Matrix(int n):A(n,vector<T>(n,T())) {}
  Matrix(int n, int m):A(n,vector<T>(m,T())) {}

  int H() const { return A.size(); }
  int W() const { return A[0].size(); }

  vector<T>& operator[] (int index) { return A[index]; }
  const vector<T>& operator[] (int index) const { return A[index]; }

  static Matrix I(int n) {
    Matrix id(n);
    for (int i =0; i < n; i++) id[i][i] = 1;
    return id;
  }

  Matrix& operator+=(const Matrix& B) {
    int n = H(), m = W();
    assert(n == B.H() && m == B.W());
    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++)
        (*this)[i][j] += B[i][j];
    return *this;
  }

  Matrix& operator-=(const Matrix& B) {
    int n = H(), m = W();
    assert(n == B.H() && m == B.W());
    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++)
        (*this)[i][j] -= B[i][j];
    return *this;
  }
  
  Matrix& operator*=(const Matrix& B) {
    int n = H(), m = W();
    int bn = B.H(), bm = B.W();
    assert(m == bn);
    vector<vector<T>> C(n,vector<T>(bm,T()));
    for (int i = 0; i < n; i++)
      for (int k = 0; k < m; k++)
        for (int j = 0; j < bm; j++)
          C[i][j] += (*this)[i][k]*B[k][j];
    A.swap(C);
    return *this;
  }

  Matrix& operator^=(ll k) {
    Matrix B = Matrix::I((*this).H());
    while(k > 0) {
      if (k&1) B *= *this;
      *this *= *this;
      k >>= 1LL;
    }
    A.swap(B.A);
    return *this;
  }

  Matrix operator+(const Matrix& B) const { return (Matrix(*this) += B); }
  Matrix operator-(const Matrix& B) const { return (Matrix(*this) -= B); }
  Matrix operator*(const Matrix& B) const { return (Matrix(*this) *= B); }
  Matrix operator^(const ll k) const { return (Matrix(*this) ^= k); }

  bool operator==(const Matrix& B) const {
    assert(H() == B.H() && W() == B.W());
    for (int i =0 ; i < H(); i++)
      for (int j = 0; j < W(); j++)
        if (A[i][j] != B[i][j]) return false;
    return true;
  }

  bool operator!=(const Matrix& B) const {
    assert(H() == B.H() && W() == B.W());
    for (int i =0 ; i < H(); i++)
      for (int j = 0; j < W(); j++)
        if (A[i][j] != B[i][j]) return true;
    return false;
  }

  // Get the determinant of the matrix in O(N^3)
  // Remember to make all n into n-1 when using with Kirchhoff's theorem
  T det() {
    int n = H(), m = W();
    assert(n == m);
    Matrix B(*this);
    T prod = 1;
    for (int i =0 ; i < n; i++) {
      int idx = -1;
      for (int j = i; j < n; j++) {
        if (B[j][i] != 0) {
          idx = j;
          break;
        }
      }
      if (idx == -1) return 0;
      if (i != idx) {
        prod *= T(-1);
        swap(B[i],B[idx]);
      }
      prod *= B[i][i];
      T inv = T(1)/B[i][i];
      for (int j =0 ; j < n; j++)
        B[i][j] *= inv;
      for (int j = i+1; j < n; j++) {
        T a = B[j][i];
        if (a==0) continue;
        for (int k = i; k < m; k++)
          B[j][k] -= B[i][k]*a;
      }
    }
    return prod;
  }
};
