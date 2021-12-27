//
// Created by prise on 12/20/21.
//

#include "plan.h"

#include "metadata.h"
#include "pixel.h"

namespace util {
Grid GenerateGrid(size_t size) {
  return util::Grid(size, std::vector<Pixel>(size));
}

inline bool Edge(int delta) { return (!delta) || (delta == timing_marker); }

template <typename T>
bool Between(const T &left, const T &right, const T &val) {
  return (val >= left && val <= right);
}

void DrawBox(util::Grid map, uint x, uint y) {
  auto position = (PixelRole::Position << 2);
  // Drawing a Box
  for (int dy = 0; dy < 7; dy++) {
    for (int dx = 0; dx < 7; dx++) {
      auto p = position;
      if (util::Edge(dx) || util::Edge(dy) ||
          (util::Between(2, 4, dx) && util::Between(2, 4, dy))) {
        p |= Pixel::Black;
      }
      map[y + dy][x + dx] = p;
    }
  }
  // White Border
  for (int dy = -1; dy < 8; dy++) {
    if (util::Between(0, static_cast<int>(map.size()),
                      static_cast<int>(y + dy))) {
      if (x > 0) {
        map[y + dy][x - 1] = position;
      }
      if (x + 7 < map.size()) {
        map[y + dy][x + 7] = position;
      }
    }
  }

  for (int dx = -1; dx < 8; dx++) {
    if (util::Between(0, static_cast<int>(map.size()),
                      static_cast<int>(x + dx))) {
      if (y > 0) {
        map[y - 1][x + dx] = position;
      }
      if (y + 7 < map.size()) {
        map[y + 7][x + dx] = position;
      }
    }
  }
}

}  // namespace util
volatile int a;
Plan::Plan(uint version)
    : version_(version), map_(util::GenerateGrid(4 * version + 17)) {
  for (uint i = 0; i < map_.size(); i++) {
    auto pixel = (PixelRole::Timing << 2);
    if (!(i & 2)) {
      pixel |= Pixel::Black;
    }
    map_[i][util::timing_marker] = pixel;
    map_[util::timing_marker][i] = pixel;
  }
  util::DrawBox(map_, 0, 0);
  util::DrawBox(map_, map_.size(), 0);
  util::DrawBox(map_, 0, map_.size() - 7);
  auto info = metadata::vtab[version];
  // todo
}
