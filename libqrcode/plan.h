//
// Created by prise on 12/20/21.
//

#ifndef QUTECODE_LIBQRCODE_PLAN_H_
#define QUTECODE_LIBQRCODE_PLAN_H_
#include <cstdint>
#include <cstdlib>
#include <vector>

#include "pixel.h"

namespace util {
const uint timing_marker = 6;  // maybe shouldn't be uint
const uint format_poly = 0x537;
const uint invert = 0x5412;
typedef std::vector<std::vector<Pixel>> Grid;

Grid GenerateGrid(size_t size);

void DrawBox(Grid map, uint x, uint y);

template <typename T>
bool Between(const T& left, const T& right, const T& val);

inline bool Edge(int delta);

uint OffsetPixel(uint offset);
}  // namespace util

class Plan {
 public:
  Plan(uint version);

 private:
  void AlignBox(uint x, uint y);
  void Format(uint level, uint mask);
  void CorrectErrors();

  uint version_;
  uint level_;

  size_t data_;            // Amount of data bytes
  size_t error_checking_;  // Amount of error-checking bytes
  size_t blocks_;          // Amount of data blocks

  util::Grid map_;  // Pixel map
};

#endif  // QUTECODE_LIBQRCODE_PLAN_H_
