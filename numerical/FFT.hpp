#include <bits/stdc++.h>
using namespace std;

// Source: neal
// Tested On:
namespace FFT {
// This is noticeably faster than std::complex for some reason.
template <typename float_t>
struct complex {
  float_t x, y;

  complex<float_t>(float_t _x = 0, float_t _y = 0) : x(_x), y(_y) {}

  float_t real() const { return x; }
  float_t imag() const { return y; }

  void real(float_t _x) { x = _x; }
  void imag(float_t _y) { y = _y; }

  complex<float_t> &operator+=(const complex<float_t> &other) {
    x += other.x;
    y += other.y;
    return *this;
  }
  complex<float_t> &operator-=(const complex<float_t> &other) {
    x -= other.x;
    y -= other.y;
    return *this;
  }

  complex<float_t> operator+(const complex<float_t> &other) const {
    return complex<float_t>(*this) += other;
  }
  complex<float_t> operator-(const complex<float_t> &other) const {
    return complex<float_t>(*this) -= other;
  }

  complex<float_t> operator*(const complex<float_t> &other) const {
    return {x * other.x - y * other.y, x * other.y + other.x * y};
  }

  complex<float_t> operator*(float_t mult) const {
    return {x * mult, y * mult};
  }

  friend complex<float_t> conj(const complex<float_t> &c) {
    return {c.x, -c.y};
  }

  friend ostream &operator<<(ostream &os, const complex<float_t> &c) {
    return os << '(' << c.x << ", " << c.y << ')';
  }
};

template <typename float_t>
complex<float_t> polar(float_t magnitude, float_t angle) {
  return {magnitude * cos(angle), magnitude * sin(angle)};
}

using float_t = double;
const float_t ONE = 1;
const float_t PI = acos(-ONE);

vector<complex<float_t>> roots = {{0, 0}, {1, 0}};
vector<int> bit_reverse;

bool is_power_of_two(int n) { return (n & (n - 1)) == 0; }

int round_up_power_two(int n) {
  while (n & (n - 1)) n = (n | (n - 1)) + 1;
  return max(n, 1);
}

// Given n (a power of two), finds k such that n == 1 << k.
int get_length(int n) {
  assert(is_power_of_two(n));
  return __builtin_ctz(n);
}

// Rearranges the indices to be sorted by lowest bit first, then second lowest,
// etc., rather than highest bit first. This makes even-odd div-conquer much
// easier.
void bit_reorder(int n, vector<complex<float_t>> &values) {
  if (int(bit_reverse.size()) != n) {
    bit_reverse.assign(n, 0);
    int length = get_length(n);
    for (int i = 1; i < n; i++)
      bit_reverse[i] = (bit_reverse[i >> 1] >> 1) | ((i & 1) << (length - 1));
  }
  for (int i = 0; i < n; i++)
    if (i < bit_reverse[i]) swap(values[i], values[bit_reverse[i]]);
}

void prepare_roots(int n) {
  if (int(roots.size()) >= n) return;

  int length = get_length(int(roots.size()));
  roots.resize(n);

  // The roots array is set up such that for a given power of two n >= 2,
  // roots[n / 2] through roots[n - 1] are the first half of the n-th roots of
  // unity.
  while (1 << length < n) {
    float_t min_angle = 2 * PI / (1 << (length + 1));

    for (int i = 0; i < 1 << (length - 1); i++) {
      int index = (1 << (length - 1)) + i;
      roots[2 * index] = roots[index];
      roots[2 * index + 1] = polar(ONE, min_angle * (2 * i + 1));
    }

    length++;
  }
}

void fft_iterative(int n, vector<complex<float_t>> &values) {
  assert(is_power_of_two(n));
  prepare_roots(n);
  bit_reorder(n, values);

  for (int len = 1; len < n; len *= 2)
    for (int start = 0; start < n; start += 2 * len)
      for (int i = 0; i < len; i++) {
        const complex<float_t> &even = values[start + i];
        complex<float_t> odd = values[start + len + i] * roots[len + i];
        values[start + len + i] = even - odd;
        values[start + i] = even + odd;
      }
}

inline complex<float_t> extract(int n, const vector<complex<float_t>> &values,
                                int index, int side) {
  if (side == -1) {
    // Return the product of 0 and 1.
    int other = (n - index) & (n - 1);
    return (conj(values[other] * values[other]) -
            values[index] * values[index]) *
           complex<float_t>(0, 0.25);
  }

  int other = (n - index) & (n - 1);
  int sign = side == 0 ? +1 : -1;
  complex<float_t> multiplier =
      side == 0 ? complex<float_t>(0.5, 0) : complex<float_t>(0, -0.5);
  return multiplier *
         complex<float_t>(values[index].real() + values[other].real() * sign,
                          values[index].imag() - values[other].imag() * sign);
}

void invert_fft(int n, vector<complex<float_t>> &values) {
  assert(n >= 2);
  for (int i = 0; i < n; i++) values[i] = conj(values[i]) * (ONE / n);
  for (int i = 0; i < n / 2; i++) {
    complex<float_t> first = values[i] + values[n / 2 + i];
    complex<float_t> second =
        (values[i] - values[n / 2 + i]) * roots[n / 2 + i];
    values[i] = first + second * complex<float_t>(0, 1);
  }
  fft_iterative(n / 2, values);
  for (int i = n - 1; i >= 0; i--)
    values[i] = i % 2 == 0 ? values[i / 2].real() : values[i / 2].imag();
}

const int FFT_CUTOFF = 150;
const float_t SPLIT_CUTOFF = 2e15;
const int SPLIT_BASE = 1 << 15;

template <typename T_out, typename T_in>
vector<T_out> square(const vector<T_in> &input) {
  if (input.empty()) return {};

  int n = int(input.size());

  // Brute force when n is small enough.
  if (n < 1.5 * FFT_CUTOFF) {
    vector<T_out> result(2 * n - 1);
    for (int i = 0; i < n; i++) {
      result[2 * i] += T_out(input[i]) * T_out(input[i]);

      for (int j = i + 1; j < n; j++)
        result[i + j] += 2 * T_out(input[i]) * T_out(input[j]);
    }
    return result;
  }

  int N = round_up_power_two(n);
  assert(N >= 2);
  prepare_roots(2 * N);
  vector<complex<float_t>> values(N, 0);

  for (int i = 0; i < n; i += 2)
    values[i / 2] = complex<float_t>(float_t(input[i]),
                                     i + 1 < n ? float_t(input[i + 1]) : 0);

  fft_iterative(N, values);

  for (int i = 0; i <= N / 2; i++) {
    int j = (N - i) & (N - 1);
    complex<float_t> even = extract(N, values, i, 0);
    complex<float_t> odd = extract(N, values, i, 1);
    complex<float_t> aux =
        even * even + odd * odd * roots[N + i] * roots[N + i];
    complex<float_t> tmp = even * odd;
    values[i] = aux - complex<float_t>(0, 2) * tmp;
    values[j] = conj(aux) - complex<float_t>(0, 2) * conj(tmp);
  }

  for (int i = 0; i < N; i++) values[i] = conj(values[i]) * (ONE / N);

  fft_iterative(N, values);
  vector<T_out> result(2 * n - 1);

  for (int i = 0; i < int(result.size()); i++) {
    float_t value = i % 2 == 0 ? values[i / 2].real() : values[i / 2].imag();
    result[i] = T_out(is_integral<T_out>::value ? round(value) : value);
  }

  return result;
}

// Note:  can be used for a 2x speedup when only the  fully overlapping
// ranges are needed. It computes results using indices modulo the power-of-two
// FFT size; see the brute force below.
template <typename T_out, typename T_in>
vector<T_out> multiply(const vector<T_in> &left, const vector<T_in> &right,
                       bool circular = false) {
  if (left.empty() || right.empty()) return {};
  if (left == right && !circular) return square<T_out>(left);
  int n = int(left.size());
  int m = int(right.size());
  int output_size = circular ? round_up_power_two(max(n, m)) : n + m - 1;
  // Brute force when either n or m is small enough.
  if (min(n, m) < FFT_CUTOFF) {
    auto &&mod_output_size = [&](int x) {
      return x < output_size ? x : x - output_size;
    };
    vector<T_out> result(output_size, 0);
    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++)
        result[mod_output_size(i + j)] += T_out(left[i]) * T_out(right[j]);
    return result;
  }
  int N = round_up_power_two(output_size);
  vector<complex<float_t>> values(N, 0);
  for (int i = 0; i < n; i++) values[i].real(float_t(left[i]));
  for (int i = 0; i < m; i++) values[i].imag(float_t(right[i]));
  fft_iterative(N, values);
  for (int i = 0; i <= N / 2; i++) {
    int j = (N - i) & (N - 1);
    complex<float_t> product_i = extract(N, values, i, -1);
    values[i] = product_i;
    values[j] = conj(product_i);
  }
  invert_fft(N, values);
  vector<T_out> result(output_size, 0);
  for (int i = 0; i < output_size; i++)
    result[i] = T_out(is_integral<T_out>::value ? round(values[i].real())
                                                : values[i].real());
  return result;
}

template <typename T>
vector<T> power(const vector<T> &v, int exponent) {
  assert(exponent >= 0);
  vector<T> result = {1};
  if (exponent == 0) return result;
  for (int k = 31 - __builtin_clz(exponent); k >= 0; k--) {
    result = multiply<T>(result, result);
    if (exponent >> k & 1) result = multiply<T>(result, v);
  }
  return result;
}

// Note:  can be used for a 2x speedup when only the  fully overlapping
// ranges are needed. It computes results using indices modulo the power-of-two
// FFT size; see the brute force below.
template <typename T>
vector<T> mod_multiply(const vector<T> &left, const vector<T> &right,
                       const int mod, bool split, bool circular = false) {
  if (left.empty() || right.empty()) return {};
  int n = int(left.size());
  int m = int(right.size());
  for (int i = 0; i < n; i++) assert(0 <= left[i] && left[i] <= mod - 1);
  for (int i = 0; i < m; i++) assert(0 <= right[i] && right[i] <= mod - 1);
  int output_size = circular ? round_up_power_two(max(n, m)) : n + m - 1;
  // Brute force when either n or m is small enough. Brute force up to higher
  // values when split = true.
  if (min(n, m) < (split ? 2 : 1) * FFT_CUTOFF) {
    auto &&mod_output_size = [&](int x) {
      return x < output_size ? x : x - output_size;
    };
    const uint64_t U64_BOUND =
        numeric_limits<uint64_t>::max() - uint64_t(mod) * mod;
    vector<uint64_t> result(output_size, 0);
    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++) {
        int index = mod_output_size(i + j);
        result[index] += uint64_t(left[i]) * uint64_t(right[j]);
        if (result[index] > U64_BOUND) result[index] %= mod;
      }
    for (uint64_t &x : result)
      if (x >= uint64_t(mod)) x %= mod;
    return vector<T>(result.begin(), result.end());
  }
  if (!split) {
    const vector<uint64_t> &product = multiply<uint64_t>(left, right, circular);
    vector<T> result(output_size, 0);
    for (int i = 0; i < output_size; i++) result[i] = T(product[i] % mod);
    return result;
  }
  int N = round_up_power_two(output_size);
  vector<complex<float_t>> left_fft(N, 0), right_fft(N, 0);
  for (int i = 0; i < n; i++) {
    left_fft[i].real(int(left[i]) % SPLIT_BASE);
    left_fft[i].imag(int(left[i]) / SPLIT_BASE);
  }
  fft_iterative(N, left_fft);
  if (left == right) {
    copy(left_fft.begin(), left_fft.end(), right_fft.begin());
  } else {
    for (int i = 0; i < m; i++) {
      right_fft[i].real(int(right[i]) % SPLIT_BASE);
      right_fft[i].imag(int(right[i]) / SPLIT_BASE);
    }
    fft_iterative(N, right_fft);
  }
  vector<complex<float_t>> product(N);
  vector<T> result(output_size, 0);

  for (int exponent = 0; exponent <= 2; exponent++) {
    uint64_t multiplier = 1;

    for (int k = 0; k < exponent; k++)
      multiplier = multiplier * SPLIT_BASE % mod;

    fill(product.begin(), product.end(), 0);

    for (int x = 0; x < 2; x++)
      for (int y = 0; y < 2; y++)
        if (x + y == exponent)
          for (int i = 0; i < N; i++)
            product[i] +=
                extract(N, left_fft, i, x) * extract(N, right_fft, i, y);

    invert_fft(N, product);

    for (int i = 0; i < output_size; i++) {
      uint64_t value = uint64_t(round(product[i].real()));
      result[i] = T((uint64_t(result[i]) + value % mod * multiplier) % mod);
    }
  }

  return result;
}
template <typename T>
vector<T> mod_power(const vector<T> &v, int exponent, const int mod,
                    bool split) {
  assert(exponent >= 0);
  vector<T> result = {1};

  if (exponent == 0) return result;

  for (int k = 31 - __builtin_clz(exponent); k >= 0; k--) {
    result = mod_multiply(result, result, mod, split);

    if (exponent >> k & 1) result = mod_multiply(result, v, mod, split);
  }

  return result;
}
// Multiplies many polynomials whose total degree is n in O(n log^2 n).
template <typename T>
vector<T> mod_multiply_all(const vector<vector<T>> &polynomials, const int mod,
                           bool split) {
  if (polynomials.empty()) return {1};

  struct compare_size {
    bool operator()(const vector<T> &x, const vector<T> &y) {
      return x.size() > y.size();
    }
  };

  priority_queue<vector<T>, vector<vector<T>>, compare_size> pq(
      polynomials.begin(), polynomials.end());

  while (pq.size() > 1) {
    vector<T> a = pq.top();
    pq.pop();
    vector<T> b = pq.top();
    pq.pop();
    pq.push(mod_multiply(a, b, mod, split));
  }
  return pq.top();
}
}  // namespace FFT
