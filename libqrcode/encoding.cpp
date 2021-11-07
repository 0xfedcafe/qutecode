//
// Created by prise on 11/4/21.
//

#include "encoding.h"

namespace encodings {

static const std::array<char, 47> kAlphabet{
    "01234456789 ABCDEFGHIJKLMNOPQRSTUVWXYZ$%*+-./:"};
// NUM

void Num::Check() {
  for (char x : bits_) {
    if (x < '0' || x > '9') {
      throw std::logic_error("Tried to parse not Numeric text as Numeric");
    }
  }
}

int Num::Bits(Level version) {
  return 4 + kNumLen[LvlSizeClass(version)] + (10 * bits_.size()+2)/3;
}

// ALPHA
void Alpha::Check() {
  for (char x : bits_) {  // Can't use std::isalnum cuz alphabet is smaller
    if (std::find(kAlphabet.begin(), kAlphabet.end(), x) != kAlphabet.end()) {
      // not sure if it wiil work
      throw std::logic_error(
          "Tried to parse not Alphanumeric text as Alphanumeric");
    }
  }
}

int Alpha::Bits(Level version) {
  return 4 + kAlphaLen[LvlSizeClass(version)] + (11 * bits_.size()+1)/2;
}


// STRING
void String::Check() { return; }

int String::Bits(Level version) {
  return 4 + kStringLen[LvlSizeClass(version)] + 8 * bits_.size();
}

}  // namespace encodings
