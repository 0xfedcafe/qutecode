//
// Created by prise on 11/7/21.
//

#ifndef QUTECODE_LIBQRCODE_BITS_H_
#define QUTECODE_LIBQRCODE_BITS_H_
#include <vector>
class Bits {
 public:
  int MSbit();
  std::vector<unsigned char> BitsCopy();
  void Append(std::vector<unsigned char>& suffix);
  void Write(unsigned int v, int inp_msbit);
  void Reset();

 private:
  std::vector<unsigned char> bits_;
  int msbit_;
};

#endif  // QUTECODE_LIBQRCODE_BITS_H_
