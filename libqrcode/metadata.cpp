//
// Created by prise on 12/27/21.
//

#include "metadata.h"

#include <cstdlib>

metadata::Version::Version(uint pos, uint stride, uint bytes, uint pattern,
                           std::vector<Level> level)
    : pos_(pos),
      stride_(stride),
      bytes_(bytes),
      pattern_(pattern),
      level_(level) {}

metadata::Level::Level(uint nblock, uint check)
    : nblock(nblock), check(check) {}

uint metadata::Version::pos() const { return pos_; }
uint metadata::Version::stride() const { return stride_; }
uint metadata::Version::bytes() const { return bytes_; }
uint metadata::Version::pattern() const { return pattern_; }
std::vector<metadata::Level> metadata::Version::level() const { return level_; }
