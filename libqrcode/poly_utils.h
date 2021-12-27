//
// Created by prise on 11/3/21.
//

#ifndef QUTECODE_LIBQRCODE_POLY_UTILS_H_
#define QUTECODE_LIBQRCODE_POLY_UTILS_H_
#include <bit>
namespace utils {

// Divide polynoms (p,q) and return remainder
[[maybe_unused]] int dividePolynoms(uint32_t p, uint32_t q) {
  unsigned int msgnbit_p = std::popcount(p);
  unsigned int msgnbit_q = std::popcount(q);
  for (; msgnbit_p >= msgnbit_q; msgnbit_p--) {
    if ((p & (1 << (msgnbit_p - 1)))) {
      p ^= q << (msgnbit_p - msgnbit_q);
    }
  }
  return p;
}

// Check if p is reducible
bool isReducible(uint32_t p) {
  unsigned int highest_bit = std::popcount(p);
  for (int q = 2; q < (1 << (highest_bit / 2 + 1)); q++) {
    if (dividePolynoms(p, q) == 0) {
      return true;
    }
  }
  return false;
}

// multiply returns the product x*y mod poly, a GF(256) multiplication.
int multiplyPolynoms(uint32_t x, uint32_t y, uint32_t poly) {
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
  }
  return z;
}

}  // namespace utils
#endif  // QUTECODE_LIBQRCODE_POLY_UTILS_H_
