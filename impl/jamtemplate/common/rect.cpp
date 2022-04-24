#include "rect.hpp"
#include <ostream>

bool jt::operator==(jt::Rectf const& a, jt::Rectf const& b)
{
    return (a.left == b.left && a.top == b.top && a.width == b.width && a.height == b.height);
}
bool jt::operator!=(jt::Rectf const& a, jt::Rectf const& b) { return !(a == b); }

std::ostream& jt::operator<<(std::ostream& os, const jt::Rectf& rect)
{
    return os << "[ (" << rect.left << ", " << rect.top << "), (" << rect.width << ", "
              << rect.height << ") ]";
}

bool jt::operator==(jt::Recti const& a, jt::Recti const& b)
{
    return (a.left == b.left && a.top == b.top && a.width == b.width && a.height == b.height);
}
bool jt::operator!=(jt::Recti const& a, jt::Recti const& b) { return !(a == b); }
