#include "rect.hpp"

namespace jt {

bool operator==(jt::Rectf const& a, jt::Rectf const& b)
{
    return (a.left == b.left && a.top == b.top && a.width == b.width && a.height == b.height);
}
bool operator!=(jt::Rectf const& a, jt::Rectf const& b) { return !(a == b); }

bool operator==(jt::Recti const& a, jt::Recti const& b)
{
    return (a.left == b.left && a.top == b.top && a.width == b.width && a.height == b.height);
}
bool operator!=(jt::Recti const& a, jt::Recti const& b) { return !(a == b); }

} // namespace jt
