//
// Created by prise on 12/27/21.
//

#ifndef QUTECODE_LIBQRCODE_METADATA_H_
#define QUTECODE_LIBQRCODE_METADATA_H_

#include <cstdlib>
#include <vector>
namespace metadata {

class Level {
 public:
  Level(uint nblock, uint check);
  uint nblock() const;
  uint check() const;

 private:
  uint nblock_;
  uint check_;
};

class Version {
 public:
  Version(uint pos, uint stride, uint bytes, uint pattern,
          std::vector<Level> level);

  uint pos() const;
  uint stride() const;
  uint bytes() const;
  uint pattern() const;
  Level level(size_t index) const;

 private:
  uint pos_;
  uint stride_;
  uint bytes_;
  uint pattern_;
  std::vector<Level> level_;
};

const Version vtab[41] = {
    {0, 0, 0, 0, {{0, 0}, {0, 0}, {0, 0}, {0, 0}}},
    {100, 100, 26, 0x0, {{1, 7}, {1, 10}, {1, 13}, {1, 17}}},           // 1
    {16, 100, 44, 0x0, {{1, 10}, {1, 16}, {1, 22}, {1, 28}}},           // 2
    {20, 100, 70, 0x0, {{1, 15}, {1, 26}, {2, 18}, {2, 22}}},           // 3
    {24, 100, 100, 0x0, {{1, 20}, {2, 18}, {2, 26}, {4, 16}}},          // 4
    {28, 100, 134, 0x0, {{1, 26}, {2, 24}, {4, 18}, {4, 22}}},          // 5
    {32, 100, 172, 0x0, {{2, 18}, {4, 16}, {4, 24}, {4, 28}}},          // 6
    {20, 16, 196, 0x7c94, {{2, 20}, {4, 18}, {6, 18}, {5, 26}}},        // 7
    {22, 18, 242, 0x85bc, {{2, 24}, {4, 22}, {6, 22}, {6, 26}}},        // 8
    {24, 20, 292, 0x9a99, {{2, 30}, {5, 22}, {8, 20}, {8, 24}}},        // 9
    {26, 22, 346, 0xa4d3, {{4, 18}, {5, 26}, {8, 24}, {8, 28}}},        // 10
    {28, 24, 404, 0xbbf6, {{4, 20}, {5, 30}, {8, 28}, {11, 24}}},       // 11
    {30, 26, 466, 0xc762, {{4, 24}, {8, 22}, {10, 26}, {11, 28}}},      // 12
    {32, 28, 532, 0xd847, {{4, 26}, {9, 22}, {12, 24}, {16, 22}}},      // 13
    {24, 20, 581, 0xe60d, {{4, 30}, {9, 24}, {16, 20}, {16, 24}}},      // 14
    {24, 22, 655, 0xf928, {{6, 22}, {10, 24}, {12, 30}, {18, 24}}},     // 15
    {24, 24, 733, 0x10b78, {{6, 24}, {10, 28}, {17, 24}, {16, 30}}},    // 16
    {28, 24, 815, 0x1145d, {{6, 28}, {11, 28}, {16, 28}, {19, 28}}},    // 17
    {28, 26, 901, 0x12a17, {{6, 30}, {13, 26}, {18, 28}, {21, 28}}},    // 18
    {28, 28, 991, 0x13532, {{7, 28}, {14, 26}, {21, 26}, {25, 26}}},    // 19
    {32, 28, 1085, 0x149a6, {{8, 28}, {16, 26}, {20, 30}, {25, 28}}},   // 20
    {26, 22, 1156, 0x15683, {{8, 28}, {17, 26}, {23, 28}, {25, 30}}},   // 21
    {24, 24, 1258, 0x168c9, {{9, 28}, {17, 28}, {23, 30}, {34, 24}}},   // 22
    {28, 24, 1364, 0x177ec, {{9, 30}, {18, 28}, {25, 30}, {30, 30}}},   // 23
    {26, 26, 1474, 0x18ec4, {{10, 30}, {20, 28}, {27, 30}, {32, 30}}},  // 24
    {30, 26, 1588, 0x191e1, {{12, 26}, {21, 28}, {29, 30}, {35, 30}}},  // 25
    {28, 28, 1706, 0x1afab, {{12, 28}, {23, 28}, {34, 28}, {37, 30}}},  // 26
    {32, 28, 1828, 0x1b08e, {{12, 30}, {25, 28}, {34, 30}, {40, 30}}},  // 27
    {24, 24, 1921, 0x1cc1a, {{13, 30}, {26, 28}, {35, 30}, {42, 30}}},  // 28
    {28, 24, 2051, 0x1d33f, {{14, 30}, {28, 28}, {38, 30}, {45, 30}}},  // 29
    {24, 26, 2185, 0x1ed75, {{15, 30}, {29, 28}, {40, 30}, {48, 30}}},  // 30
    {28, 26, 2323, 0x1f250, {{16, 30}, {31, 28}, {43, 30}, {51, 30}}},  // 31
    {32, 26, 2465, 0x209d5, {{17, 30}, {33, 28}, {45, 30}, {54, 30}}},  // 32
    {28, 28, 2611, 0x216f0, {{18, 30}, {35, 28}, {48, 30}, {57, 30}}},  // 33
    {32, 28, 2761, 0x228ba, {{19, 30}, {37, 28}, {51, 30}, {60, 30}}},  // 34
    {28, 24, 2876, 0x2379f, {{19, 30}, {38, 28}, {53, 30}, {63, 30}}},  // 35
    {22, 26, 3034, 0x24b0b, {{20, 30}, {40, 28}, {56, 30}, {66, 30}}},  // 36
    {26, 26, 3196, 0x2542e, {{21, 30}, {43, 28}, {59, 30}, {70, 30}}},  // 37
    {30, 26, 3362, 0x26a64, {{22, 30}, {45, 28}, {62, 30}, {74, 30}}},  // 38
    {24, 28, 3532, 0x27541, {{24, 30}, {47, 28}, {65, 30}, {77, 30}}},  // 39
    {28, 28, 3706, 0x28c69, {{25, 30}, {49, 28}, {68, 30}, {81, 30}}},  // 40
};

}  // namespace metadata

#endif  // QUTECODE_LIBQRCODE_METADATA_H_
