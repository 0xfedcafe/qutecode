//
// Created by prise on 11/4/21.
//

#ifndef QUTECODE_LIBQRCODE_ENCODING_H_
#define QUTECODE_LIBQRCODE_ENCODING_H_

namespace encodings {
using Level = unsigned char;
class Alpha {
  void Check();
  int Bits(Level version);
  void Encode(std::vector<unsigned int>& bits, Level level);
};

class Num {
  void Check();
  int Bits(Level version);
  void Encode(std::vector<unsigned int>& bits, Level level);
};

class String {
  void Check();
  int Bits(Level version);
  void Encode(std::vector<unsigned int>& bits, Level level);
};
template <class EncodeType>
class Encoder : EncodeType {

};
}  // namespace encodings

#endif  // QUTECODE_LIBQRCODE_ENCODING_H_
