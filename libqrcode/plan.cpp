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

void Plan::AlignBox(uint x, uint y) {
  auto align = (PixelRole::Alignment << 2);
  for (uint dy = 0; dy < 5; dy++) {
    for (uint dx = 0; dx < 5; dx++) {
      auto p = align;
      if (dx == 0 || dx == 4 || dy == 0 || dy == 4 || dx == 2 || dy == 2) {
        p |= Pixel::Black;
      }
      map_[y + dy][x + dx] = p;
    }
  }
}

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
  auto info = metadata::vtab[version_];
  for (uint x = 4; x + 5 < map_.size();) {
    for (uint y = 4; y + 5 < map_.size();) {
      // don't overwrite timinig markers
      if (!((x < 7 && y < 7) || ((x < 7) && (y + 5 >= (map_.size() - 7))) ||
            (x + 5 >= map_.size() - 7 && y < 7))) {
        AlignBox(x, y);
      }
      if (y == 4) {
        y = info.pos();
      } else {
        y += info.stride();
      }
    }
    if (x == 4) {
      x = info.pos();
    } else {
      x += info.stride();
    }
  }
  auto pattern = metadata::vtab[version_].pattern();
  if (pattern != 0) {
    version = pattern;
    for (uint dx = 0; dx < 6; dx++) {
      for (uint dy = 0; dy < 3; dy++) {
        auto pixel = (PixelRole::PVersion << 2);
        if (version & 1) {
          pixel |= Pixel::Black;
          map_[map_.size() - 11 + dy][dx] = pixel;
          map_[dx][map_.size() - 11 + dy] = pixel;
          version >>= 1;
        }
      }
    }
  }
  // one lonely black pixel
  map_[map_.size() - 8][8] = (PixelRole::Unused << 2) | Pixel::Black;
}

void Plan::FormatPlan(uint32_t level, uint32_t mask) {
  uint fb = (level ^ 1) << 13;
  fb |= (mask << 10);
  uint rem = fb;
  for (uint i = 14; i >= 10; i--) {
    if (rem & (1 << i)) {
      rem ^= (util::format_poly << (i - 10));
    }
  }
  fb |= rem;
  for (uint i = 0; i < 15; i++) {
    auto pixel = (PixelRole::Format << 2) + Pixel::GetOffset(i);
    if ((fb >> i) & 1) {
      pixel |= Pixel::Black;
    }
    if ((util::invert >> i) & 1) {
      pixel ^= Pixel::Black | Pixel::Invert;
    }

    // top left
    if (i < 6) {
      map_[i][8] = pixel;
    } else if (i == 6 || i == 7) {
      map_[i + 1][8] = pixel;
    } else if (i == 8) {
      map_[8][7] = pixel;
    } else {
      map_[8][14 - i] = pixel;
    }

    if (i < 8) {
      map_[8][map_.size() - i] = pixel;
    } else {
      map_[map_.size() - 1 - (14 - i)][8] = pixel;
    }
  }
}

void Plan::CorrectErrors() {
  auto nblock = metadata::vtab[version_].level(level_).nblock();
  auto ne = metadata::vtab[version_].level(level_).check();
  auto nde = (metadata::vtab[version_].bytes() - ne * blocks_) / blocks_;
  auto extra = (metadata::vtab[version_].bytes() - ne * blocks_) % blocks_;
}