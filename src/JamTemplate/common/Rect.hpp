#ifndef GUARD_JAMTEMPLATE_RECT_GUARD_HPP_12345
#define GUARD_JAMTEMPLATE_RECT_GUARD_HPP_12345

#include "rect_lib.hpp"

namespace jt {

bool operator==(jt::rect const& a, jt::rect const& b);
bool operator!=(jt::rect const& a, jt::rect const& b);

bool operator==(jt::recti const& a, jt::recti const& b);
bool operator!=(jt::recti const& a, jt::recti const& b);

} // namespace jt
#endif
