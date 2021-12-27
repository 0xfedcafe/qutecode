//
// Created by prise on 12/27/21.
//

#include "metadata.h"

metadata::Version::Version(uint pos, uint stride, uint bytes, uint pattern,
                           std::vector<Level> level)
    : pos_(pos),
      stride_(stride),
      bytes_(bytes),
      pattern_(pattern),
      level_(level) {}

metadata::Level::Level(uint nblock, uint check)
    : nblock(nblock), check(check) {}
