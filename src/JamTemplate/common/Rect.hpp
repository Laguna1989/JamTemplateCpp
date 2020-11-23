﻿#ifndef RECT_GUARD_HPP_12345
#define RECT_GUARD_HPP_12345

#include "rect_base.hpp"

namespace jt {

bool operator==(jt::rect const& a, jt::rect const& b);
bool operator!=(jt::rect const& a, jt::rect const& b);

bool operator==(jt::recti const& a, jt::recti const& b);
bool operator!=(jt::recti const& a, jt::recti const& b);

} // namespace jt
#endif