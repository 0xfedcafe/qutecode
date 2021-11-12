//
// Created by prise on 11/4/21.
//

#include "encoding.h"

namespace encodings {

static const std::array<char, 47> kAlphabet{
    "01234456789 ABCDEFGHIJKLMNOPQRSTUVWXYZ$%*+-./:"};
// NUM

void Num::Check() {
  for (char x : data_) {
    if (x < '0' || x > '9') {
      throw std::logic_error("Tried to parse not Numeric text as Numeric");
    }
  }
}

int Num::BitsCnt(Level version) {
  return 4 + kNumLen[LvlSizeClass(version)] + (10 * data_.size() + 2) / 3;
}

void Num::Encode(Bits &bits, Level level) {
  bits.Write(1, 4);
  bits.Write(data_.size(), kNumLen[LvlSizeClass(level)]);
  int i;
  for (i = 0; i + 3 <= data_.size(); i += 3) {
    bits.Write(
        (data_[i] - '0') * 100 + (data_[i + 1] - '0') * 10 + data_[i + 2] - '0',
        10);
    if (data_.size() - i == 1) {
      bits.Write(data_[i] - '0', 4);
    } else {
      bits.Write((data_[i] - '0') * 10 + (data_[i + 1] - '0'), 7);
    }
    // probably casts to uint required
  }
}

// ALPHA
void Alpha::Check() {
  for (char x : data_) {  // Can't use std::isalnum cuz alphabet is smaller
    if (std::find(kAlphabet.begin(), kAlphabet.end(), x) != kAlphabet.end()) {
      // not sure if it wiil work
      throw std::logic_error(
          "Tried to parse not Alphanumeric text as Alphanumeric");
    }
  }
}

int Alpha::BitsCnt(Level version) {
  return 4 + kAlphaLen[LvlSizeClass(version)] + (11 * data_.size() + 1) / 2;
}

void Alpha::Encode(Bits &bits, Level level) {
  bits.Write(2,4);
  bits.Write(data_.size(), kAlphaLen[LvlSizeClass(level)]);
  int i;
  for(int i = 0; i +2 <= data_.size(); i+=2) {

  }
}

// STRING
void String::Check() { return; }

int String::BitsCnt(Level version) {
  return 4 + kStringLen[LvlSizeClass(version)] + 8 * data_.size();
}

}  // namespace encodings
