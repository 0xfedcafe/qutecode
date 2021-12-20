//
// Created by prise on 12/19/21.
//

#include "code.h"

bool Code::Black(std::pair<size_t, size_t> coords) {
  0 <= coords.first&& coords.first < size_ &&
      0 <= coords.second&& coords.second < size_ &&
      (bitmap_[coords.second * stride_ + coords.first / 8] &
       (1 << u_int32_t(7 - coords.first & 7))) != 0;
}

bool Mask::Invert(std::pair<size_t, size_t> coords) {  // y, x
  if (m_ < 0) {
    return false;
  }
  return mask_func[m_](coords.first, coords.second);
}