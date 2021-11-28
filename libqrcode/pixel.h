//
// Created by prise on 11/28/21.
//

#ifndef QUTECODE_LIBQRCODE_PIXEL_H_
#define QUTECODE_LIBQRCODE_PIXEL_H_
#include <string>
class Pixel {
  int val_;
};

class PixelRole {
  enum {
    Position,   // position squares (large)
    Alignment,  // alignment squares (small)
    Timing,     // timing strip between position squares
    Format,     // format metadata
    PVersion,   // version pattern
    Unused,     // unused pixel
    Data,       // data bit
    Check,      // error correction check bit
    Extra,
  };
  Pixel Pixel();
  std::string String();
  int val_;
};
#endif  // QUTECODE_LIBQRCODE_PIXEL_H_
