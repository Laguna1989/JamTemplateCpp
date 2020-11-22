#include "rect.hpp"

namespace jt {

bool operator==(jt::rect const& a, jt::rect const& b)
{
    return (a.left() == b.left() && a.top() == b.top() && a.width() == b.width()
        && a.height() == b.height());
}
bool operator!=(jt::rect const& a, jt::rect const& b) { return !(a == b); }

bool operator==(jt::recti const& a, jt::recti const& b)
{
    return (a.left() == b.left() && a.top() == b.top() && a.width() == b.width()
        && a.height() == b.height());
}
bool operator!=(jt::recti const& a, jt::recti const& b) { return !(a == b); }

} // namespace jt
