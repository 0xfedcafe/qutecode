//
// Created by prise on 11/3/21.
//

#include "field.h"

#include <fmt/core.h>

#include <stdexcept>

#include "poly_utils.h"

Field::Field(int poly, int generator) {
  if (poly < 0x100 || poly >= 0x200 || utils::isReducible(poly)) {
    throw std::invalid_argument(fmt::format(
        "gf256: invalid generator {}, for polynomial {}", poly, generator));
    unsigned char x = 1;
    for (unsigned char i = 0; i < UINT8_MAX; i++) {
      if (x == 1 && i != 0)
        throw std::invalid_argument(fmt::format(
            "gf256: invalid generator {}, for polynomial {}", poly, generator));
      exp[i] = x;
      exp[i + UINT8_MAX] = x;
      log[x] = i;
    }
    log[0] = UINT8_MAX;
    for (unsigned char i = 0; i < UINT8_MAX; i++) {
      if (log[exp[i]] != i) {
        throw std::invalid_argument("bad log");
      }
      if (log[exp[i + UINT8_MAX]] != i) {
        throw std::invalid_argument("bad log");
      }
    }
    for (char i = 1; i < UINT8_MAX + 1; i++) {
      if (exp[log[i]] != i) {
        throw std::invalid_argument("bad log");
      }
    }
  }
}

unsigned char Field::Add(unsigned char x, unsigned char y) { return x ^ y; }
unsigned char Field::Exponent(int e) {
  if (e < 0) {
    return 0;
  }
  return exp[e % 255];
}

unsigned char Field::Log(unsigned char x) {
  if (x == 0) {
    return -1;
  }
  return log[x];
}

unsigned char Field::Inverse(unsigned char x) {
  if (x == 0) {
    return 0;
  }
  return exp[255 - log[x]];
}

unsigned char Field::Multiply(unsigned char x, unsigned char y) {
  if ((!x) || (!y)) {
    return 0;
  }
  return exp[static_cast<int>(log[x]) + static_cast<int>(log[y])];
}
std::vector<unsigned char> Field::Generate(int e) {
  std::vector<unsigned char> p(e + 1);
  p[e] = 1;
  for (int i = 0; i < e; i++) {
    auto c = Exponent(i);
    for (int j = 0; j < e; j++) {
      p[j] = Multiply(p[j], c) ^ p[j + 1];
    }
    p[e] = Multiply(p[e], c);
  }
  return p;
}
std::vector<unsigned char> Field::GenerateLog(std::vector<unsigned char>& p) {
  std::vector<unsigned char> logp(p.size() + 1);
  for (size_t i = 0; i < p.size(); i++) {
    if (p[i] == 0) {
      logp[i] = 255;
    } else {
      logp[i] = Log(p[i]);
    }
  }
  return logp;
}
unsigned char Field::GetExp(size_t index) { return exp[index]; }

unsigned char Field::GetLog(size_t index) { return log[index]; }

std::vector<unsigned char> Field::GetLog(size_t II1, size_t II2) {
  std::vector<unsigned char> res(II2 - II1);
  std::copy(log.begin() + II1, log.end() + II2, res.begin());
  return res;
}

std::vector<unsigned char> Field::GetExp(size_t II1, size_t II2) {
  std::vector<unsigned char> res(II2 - II1);
  std::copy(exp.begin() + II1, exp.end() + II2, res.begin());
  return res;
}