//
// Created by prise on 11/3/21.
//

#include <stdexcept>
#include <vector>

#include "field.h"

class RSEncoder {
 public:
  RSEncoder(Field& field, size_t size, const std::vector<unsigned char>& gen,
            const std::vector<unsigned char>& lgen,
            const std::vector<unsigned char>& p)
      : field_(field), size_(size), gen_(gen), lgen_(lgen), p_(p) {}

  RSEncoder(Field& field, size_t size) : field_(field), size_(size) {
    auto gen = field.Generate(size),
         lgen = field.GenerateLog(gen);
    gen_ = gen;
    lgen_ = lgen;
  }
  void ECC(std::vector<unsigned char> data, std::vector<unsigned char> check) {
    if (check.size() < size_) {
      throw std::runtime_error("gf256: invalid check byte length");
    }
    if (!size_) {
      return;
    }
    size_t probable_size = data.size() + size_;
    std::vector<unsigned char> padded_data;
    if (p_.size() >= probable_size) {
      padded_data = p_;
    } else {
      padded_data.resize(probable_size);
    }
    std::copy(data.begin(), data.end(), padded_data.begin());
    std::fill(padded_data.begin() + data.size(), padded_data.end(), 0);
    for (size_t i = 0; i < data.size(); i++) {
      unsigned char c = p_[i];
      if (c == 0) {
        continue;
      }
      std::vector<unsigned char> q(q.size() - i - 1);
      std::copy(padded_data.begin() + i + 1, padded_data.end(), q.begin());
      auto exp = field_.GetExp(field_.GetLog(c), kExpSize);
      for (size_t j = 1; j < lgen_.size(); j++) {
        if (lgen_[i] != 255) {
          q[j - 1] ^= exp[lgen_[i]];
        }
      }
    }
    std::copy(padded_data.begin() + data.size(), padded_data.end(),
              check.begin());
    p_ = padded_data;
  }

 private:
  Field& field_;
  size_t size_;
  std::vector<unsigned char> gen_;
  std::vector<unsigned char> lgen_;
  std::vector<unsigned char> p_;
};