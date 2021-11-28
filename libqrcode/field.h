//
// Created by prise on 11/3/21.
//

#ifndef QUTECODE_LIBQRCODE_FIELD_H_
#define QUTECODE_LIBQRCODE_FIELD_H_

#include <array>
#include <tuple>
#include <vector>

#define kExpSize 510
#define kLogSize 256

class Field {
 public:
  Field(int poly, int generator);
  std::vector<unsigned char> Generate(int e);
  std::vector<unsigned char> GenerateLog(std::vector<unsigned char>& e);
  unsigned char GetLog(size_t II1);
  std::vector<unsigned char> GetLog(size_t II1,size_t II2);
  unsigned char GetExp(size_t II1);
  std::vector<unsigned char> GetExp(size_t II1, size_t II2);

 private:
  std::array<unsigned char, kLogSize> log;
  std::array<unsigned char, kExpSize> exp;

  unsigned char Add(unsigned char x, unsigned char y);

  unsigned char Exponent(int e);

  unsigned char Log(unsigned char x);

  unsigned char Inverse(unsigned char x);

  unsigned char Multiply(unsigned char x, unsigned char y);
};

#endif  // QUTECODE_LIBQRCODE_FIELD_H_
