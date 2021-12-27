//
// Created by prise on 12/19/21.
//

#include "code.h"

bool Code::Black(std::pair<size_t, size_t> coords) {
  return (coords.first < size_ &&
          coords.second <
              size_ &&  // probably should use not size_t, but signed int
          (bitmap_[coords.second * stride_ + coords.first / 8] &
           (1 << u_int32_t(7 - (coords.first & 7)))) != 0);
}

bool Mask::Invert(std::pair<size_t, size_t> coords) {  // y, x
  return mask_func[mask_type_](coords.first, coords.second);
}