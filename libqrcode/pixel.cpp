//
// Created by prise on 11/28/21.
//

#include "pixel.h"

#include <array>

std::array<std::string, 9> roles = {
    "position", "alignment", "timing", "format", "pversion",
    "unused",   "data",      "check",  "extra",
};
// PixelRole Methods

std::string PixelRole::String() {
  if (PixelRole::Position <= val_ && val_ <= PixelRole::Check) {
    return roles[val_];
  }
  return std::to_string(val_);
}

Pixel::Pixel(int init) : val_(init){};
Pixel::Pixel() : val_(0) {};

PixelRole::PixelRole(int init) : val_(init){};

int PixelRole::GetVal() { return val_; }

// End of PixelRole Methods

// Pixel Methods

PixelRole Pixel::GetRole() { return (PixelRole(val_ >> 2).GetVal() & 15); }

uint32_t Pixel::GetOffset() { return uint(val_ >> 6); }

Pixel Pixel::OffsetPixel(uint32_t offset) { return Pixel(offset >> 6); }

std::string Pixel::String() {
  auto s = GetRole().String();
  if (val_ & Pixel::Black) {
    s += "+black";
  }
  if (val_ & Pixel::Invert) {
    s += "+invert";
  }
  s += "+" + std::to_string(GetOffset());
  return s;
}

// End of Pixel Methods