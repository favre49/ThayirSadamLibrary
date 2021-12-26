#include <bits/stdc++.h>
using namespace std;

// Source: Lain
// Tested on: https://judge.yosupo.jp/problem/matrix_det, https://judge.yosupo.jp/problem/inverse_matrix
// 
// Matrix class for general applications
template <typename T>
struct Matrix {
  public:
    Matrix() = default;
    Matrix(int n, int m) : n(n), m(m), A(n, vector<T>(m,T())) {}

    static Matrix I(int n) {
      Matrix identity(n,n);
      for (int i = 0; i < n; i++)
        identity[i][i] = 1;
      return identity;
    }

    int N() const { return A.size(); }
    int M() const { return A[0].size(); }

    vector<T>& operator[] (int index) { return A[index]; }
    const vector<T>& operator[] (int index) const { return A[index]; }

    Matrix& operator+=(const Matrix& B) {
      int n = N(), m = M();
      assert(n == B.N() && m == B.M());
      for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
          (*this)[i][j] += B[i][j];
      return *this;
    }

    Matrix& operator-=(const Matrix& B) {
      int n = N(), m = M();
      assert(n == B.N() && m == B.M());
      for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
          (*this)[i][j] -= B[i][j];
      return *this;
    }

    Matrix& operator*=(const Matrix& B) {
      int n = N(), m = M();
      int bn = B.N(), bm = B.M();
      assert(m == bn);
      vector<vector<T>> C(n,vector<T>(bm,T()));
      for (int i = 0; i < n; i++)
        for (int k = 0; k < m; k++) 
          for (int j = 0; j < bm; j++)
            C[i][j] += (*this)[i][k]*B[k][j];
      A.swap(C);
      return *this;
    }

    Matrix& operator*=(const T& a) {
      int n = N(), m= M();
      for (int i =0 ; i < n; i++)
        for (int j =0 ; j < m; j++)
          (*this)[i][j] *= a;
      return *this;
    }

    Matrix& operator/=(const T& a) {
      int n = N(), m= M();
      for (int i =0 ; i < n; i++)
        for (int j =0 ; j < m; j++)
          (*this)[i][j] /= a;
      return *this;
    }

    bool operator==(const Matrix& B) const {
      int n = N(), m = M();
      if (n != B.N() || m != B.M()) return false;
      for (int i = 0; i < n; i++) 
        for (int j  = 0; j < m; j++)
          if (A[i][j] != B[i][j])
            return false;
      return true;
    }

    bool operator!=(const Matrix& B) const {
      int n = N(), m = M();
      if (n != B.N() || m != B.M()) return true;
      for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
          if (A[i][j] != B[i][j])
            return true;
      return false;
    }

    friend ostream &operator<<(ostream& os, const Matrix& A) {
      int n = A.N(), m = A.M();
      os << "Matrix with dimensions " << n << "x" << m << '\n';
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
          os << A[i][j] << " ";
        os << '\n';
      }
      return os;
    }

    friend istream &operator>>(istream& is, Matrix& A) {
      for (auto& row : A.A)
        for (auto& col : row)
          is >> col;
      return is;
    }

    friend vector<T> operator*(const Matrix& A, const vector<T>& v) {
      int n = A.N(), m = A.M();
      assert(m == v.size());
      vector<T> ret(n);
      for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
          ret[i] += A[i][j] * v[j];
      return ret;
    }

    friend vector<T> operator*(const vector<T>& v, const Matrix& A) {
      int n = A.N(), m = A.M();
      assert(n == v.size());
      vector<T> ret(m);
      for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
          ret[j] += A[i][j] * v[j];
      return ret;
    }

    Matrix operator+(const Matrix& B) const { return (Matrix(*this) += B); }
    Matrix operator-(const Matrix& B) const { return (Matrix(*this) -= B); }
    Matrix operator*(const Matrix& B) const { return (Matrix(*this) *= B); }
    Matrix operator*(const T& a) const { return (Matrix(*this) *= a); }
    Matrix operator/(const T& a) const { return (Matrix(*this) /= a); }

    Matrix pow(int64_t k) const {
      Matrix B = Matrix::I(N());
      bool is_identity = true;
      if (k == 0) return B;
      for (int i = 63 - __builtin_clzll(k); i >= 0; i--) {
        if (!is_identity) B *= B;
        if ((k>>i)&1) {
          B *= (*this);
          is_identity = false;
        }
      }
      return B;
    }

    Matrix transpose() const {
      int n = N(), m = M();
      Matrix B(n,m);
      for (int i = 0; i < n; i++)
        for (int j =0; j < m; j++)
          B[i][j] = A[j][i];
      return B;
    }

    int inverse() {
      int n = N(), m = M();
      assert(n == m);
      int rank = 0;
      Matrix ret = Matrix::I(n), tmp = *this;
      for (int i = 0; i < n; i++) {
        int ptr = i;
        while(ptr < n && tmp[ptr][i] == 0) ptr++;
        if (ptr == n) continue;
        rank++;
        ret[i].swap(ret[ptr]), tmp[i].swap(tmp[ptr]);
        T inv = T(1)/tmp[i][i];
        for (int j = 0; j < m; j++)
          ret[i][j] *= inv;
        for (int j = i+1; j < m; j++)
          tmp[i][j] *= inv;
        for (int h = 0; h < n; h++) {
          if (i == h) continue;
          const T c = -tmp[h][i];
          for (int j = 0; j < m; j++)
            ret[h][j] += ret[i][j]*c;
          for (int j = i+1; j < m; j++)
            tmp[h][j] += tmp[i][j]*c;
        }
      }
      swap(A,ret.A);
      return rank;
    }

    T determinant() {
      int n = N(), m = M();
      assert(n == m);
      Matrix B(*this);
      T prod = 1;
      for (int i = 0; i < n; i++) {
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
          swap(B[i], B[idx]);
        }
        prod *= B[i][i];
        T inv = T(1)/B[i][i];
        for (int j = 0; j < n; j++)
          B[i][j] *= inv;
        for (int j = i+1; j < n; j++) {
          T a = B[j][i];
          if (a== 0) continue;
          for (int k = i; k < m; k++)
            B[j][k] -= B[i][k]*a;
        }
      }
      return prod;
    }

  private:
    size_t n, m;
    vector<vector<T>> A;
};

