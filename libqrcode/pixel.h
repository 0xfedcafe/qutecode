//
// Created by prise on 11/28/21.
//

#ifndef QUTECODE_LIBQRCODE_PIXEL_H_
#define QUTECODE_LIBQRCODE_PIXEL_H_
#include <string>

class Pixel;

class PixelRole {
  enum {
    Position = 1,  // position squares (large)
    Alignment,     // alignment squares (small)
    Timing,        // timing strip between position squares
    Format,        // format metadata
    PVersion,      // version pattern
    Unused,        // unused pixel
    Data,          // data bit
    Check,         // error correction check bit
    Extra,
  };

 public:
  PixelRole(int init);
  Pixel GetPixel();
  int GetVal();
  std::string String();
  int val_;
};

class Pixel {
  enum { Black = 1, Invert };

 public:
  Pixel(int init);
  PixelRole GetRole();
  uint32_t GetOffset();
  Pixel OffsetPixel(uint32_t offset);
  std::string String();

 private:
  int val_;
};

#endif  // QUTECODE_LIBQRCODE_PIXEL_H_
