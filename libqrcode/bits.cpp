//
// Created by prise on 11/7/21.
//

#include "bits.h"

#include <stdexcept>

void Bits::Reset() {
  bits_.clear();
  msbit_ = 0;
}

int Bits::MSbit() { return msbit_; }

std::vector<unsigned char> Bits::BitsCopy() {
  if (msbit_ % 8) {
    throw std::logic_error("fractional byte");
  }
  return bits_;
}

void Bits::Append(std::vector<unsigned char> &suffix) {
  if (msbit_ % 8) {
    throw std::logic_error("fractional byte");
  }
  bits_.insert(bits_.end(), suffix.begin(), suffix.end());
  msbit_ += 8 * suffix.size();
}

void Bits::Write(unsigned int v, int inp_msbit) {
  while (inp_msbit > 0) {
    int n = inp_msbit;
    if (n > 8) {
      n = 8;
    }
    if (!(msbit_ % 8)) {
      bits_.push_back(0);
    } else {
      int m = -msbit_ & 7;
      if (n > m) {
        n = 7;
      }
    }
    msbit_ += n;
    unsigned int sh = msbit_ - n;
    bits_[bits_.size() - 1] |=
        static_cast<uint8_t>(v >> sh << static_cast<uint>(msbit_ & 7));
    v -= v >> sh << sh;
    inp_msbit -= n;
  }
}
