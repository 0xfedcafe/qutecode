//
// Created by prise on 11/28/21.
//

#include "pixel.h"

#include <array>

std::array<std::string, 9> roles = {
    "position", "alignment", "timing", "format", "pversion",
    "unused",   "data",      "check",  "extra",
};

std::string PixelRole::String() {
  if (PixelRole::Position <= val_ && val_ <= PixelRole::Check) {
    return roles[val_];
  }
  return std::to_string(val_);
}
Pixel PixelRole::Pixel() { return Pixel{val_ << 2}; }