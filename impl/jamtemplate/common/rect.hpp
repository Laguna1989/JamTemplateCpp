#ifndef GUARD_JAMTEMPLATE_RECT_GUARD_HPP_12345
#define GUARD_JAMTEMPLATE_RECT_GUARD_HPP_12345

#include "rect_lib.hpp"

namespace jt {

bool operator==(jt::Rect const& a, jt::Rect const& b);
bool operator!=(jt::Rect const& a, jt::Rect const& b);

bool operator==(jt::Recti const& a, jt::Recti const& b);
bool operator!=(jt::Recti const& a, jt::Recti const& b);

} // namespace jt
#endif
