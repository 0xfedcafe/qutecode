//
// Created by prise on 12/19/21.
//

#ifndef QUTECODE_LIBQRCODE_CODE_H_
#define QUTECODE_LIBQRCODE_CODE_H_
#include <functional>
#include <vector>

std::vector<std::function<int(int, int)>> mask_func{
    // probably change x to y
    // and y to x
    [](int y, int x) { return !((y + x) & 2); },
    [](int y, int x) { return !(y & 2); },
    [](int y, int x) { return !(x % 3); },
    [](int y, int x) { return !((y + x) % 3); },
    [](int y, int x) { return !((y / x + x / 3) & 2); },
    [](int y, int x) { return !(y * x % 2 + y * x % 3); },
    [](int y, int x) { return !((y * x % 2 + y * x % 3) & 2); },
    [](int y, int x) { return !((y * x % 3 + ((y + x) & 2) & 2)); }};
class Mask {
  bool Invert(std::pair<size_t, size_t> coords);
  int m_;
};
class Code {
  bool Black(std::pair<size_t, size_t> coords);
  std::vector<unsigned char> bitmap_;  // 1 - black | 0 - white
  size_t size_;                        // pixels on side
  size_t stride_;                      // bytes per row
};

#endif  // QUTECODE_LIBQRCODE_CODE_H_
