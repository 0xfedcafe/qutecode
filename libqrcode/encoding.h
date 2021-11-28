//
// Created by prise on 11/4/21.
//

#ifndef QUTECODE_LIBQRCODE_ENCODING_H_
#define QUTECODE_LIBQRCODE_ENCODING_H_

#include <algorithm>
#include <string>
#include <vector>

#include "bits.h"

namespace encodings {
using Level = unsigned char;
int LvlSizeClass(Level l) {
  if (l <= 9) {
    return 0;
  } else if (l <= 26) {
    return 1;
  } else {
    return 2;
  }
}
static const int kNumLen[3] = {10, 12, 14};
static const int kAlphaLen[3] = {9, 11, 13};
static const int kStringLen[3] = {8, 16, 16};
static const int kMinVersion = 1;
static const int kMaxVersion = 40;

class Alpha {
  void Check();
  void Encode(Bits& bits, Level level);
  int BitsCnt(Level version);
  std::string data_;
};

class Num {
  void Check();
  void Encode(Bits& bits, Level level);
  int BitsCnt(Level version);
  std::string data_;
};

class String {
  void Check();
  void Encode(Bits& bits, Level level);
  int BitsCnt(Level version);
  std::string data_;
};
template <class EncodeType>
class Encoder : EncodeType {};

using AlphaEncoder = Encoder<Alpha>;
using NumEncoder = Encoder<Num>;
using StringEncoder = Encoder<String>;

}  // namespace encodings

#endif  // QUTECODE_LIBQRCODE_ENCODING_H_
