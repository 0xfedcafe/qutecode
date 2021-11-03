//
// Created by prise on 11/3/21.
//

#ifndef QUTECODE_LIBQRCODE_POLY_UTILS_H_
#define QUTECODE_LIBQRCODE_POLY_UTILS_H_
namespace utils {

// Returns the most significant bit
unsigned int msgnbit(int p) {
  unsigned int n = 0;
  for (; p > 0; p >>= 1) {
    n++;
  }
  return n;
}

// Divide polynoms (p,q) and return remainder
[[maybe_unused]] int dividePolynoms(int p, int q) {
  unsigned int msgnbit_p = msgnbit(p);
  unsigned int msgnbit_q = msgnbit(q);
  for (; msgnbit_p >= msgnbit_q; msgnbit_p--) {
    if (p & (1 << (msgnbit_p - 1)) != 0) {
      p ^= q << (msgnbit_p - msgnbit_q);
    }
  }
  return p;
}

// Check if p is reducible
bool isReducible(int p) {
  unsigned int highest_bit = msgnbit(p);
  for (int q = 2; q < (1 << (highest_bit / 2 + 1)); q++) {
    if (dividePolynoms(p, q) == 0) {
      return true;
    } else {
      return false;
    }
  }
}

// multiply returns the product x*y mod poly, a GF(256) multiplication.
int multiplyPolynoms(int x, int y, int poly) {
  int z = 0;
  while (x > 0) {
    if (x & 1) {
      z ^= y;
    }
    x >>= 1;
    y <<= 1;
    if (y & 0x100) {
      y ^= poly;
    }
    return z;
  }
}

}  // namespace utils
#endif  // QUTECODE_LIBQRCODE_POLY_UTILS_H_
