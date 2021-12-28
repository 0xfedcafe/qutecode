//
// Created by prise on 12/27/21.
//

#include "metadata.h"

#include <cstdlib>
// Version Begin
metadata::Version::Version(uint pos, uint stride, uint bytes, uint pattern,
                           std::vector<Level> level)
    : pos_(pos),
      stride_(stride),
      bytes_(bytes),
      pattern_(pattern),
      level_(level) {}

uint metadata::Version::pos() const { return pos_; }
uint metadata::Version::stride() const { return stride_; }
uint metadata::Version::bytes() const { return bytes_; }
uint metadata::Version::pattern() const { return pattern_; }
metadata::Level metadata::Version::level(size_t index) const {
  return level_[index];
}

// Version End

// Level begin
metadata::Level::Level(uint nblock, uint check)
    : nblock_(nblock), check_(check) {}

uint metadata::Level::nblock() const { return nblock_; }
uint metadata::Level::check() const { return check_; }
// Level end