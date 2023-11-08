#include "rect.hpp"
#include <ostream>

jt::Rectf::Rectf()
    : left { 0.0f }
    , top { 0.0f }
    , width { 0.0f }
    , height { 0.0f }
{
}

jt::Rectf::Rectf(float l, float t, float w, float h)
    : left { l }
    , top { t }
    , width { w }
    , height { h }
{
}

bool jt::operator==(jt::Rectf const& a, jt::Rectf const& b)
{
    return (a.left == b.left && a.top == b.top && a.width == b.width && a.height == b.height);
}

bool jt::operator!=(jt::Rectf const& a, jt::Rectf const& b) { return !(a == b); }

std::ostream& jt::operator<<(std::ostream& os, jt::Rectf const& rect)
{
    return os << "[ (" << rect.left << ", " << rect.top << "), (" << rect.width << ", "
              << rect.height << ") ]";
}

jt::Recti::Recti(int l, int t, int w, int h)
    : left { l }
    , top { t }
    , width { w }
    , height { h }
{
}

bool jt::operator==(jt::Recti const& a, jt::Recti const& b)
{
    return (a.left == b.left && a.top == b.top && a.width == b.width && a.height == b.height);
}

bool jt::operator!=(jt::Recti const& a, jt::Recti const& b) { return !(a == b); }

jt::Recti::Recti()
    : left { 0 }
    , top { 0 }
    , width { 0 }
    , height { 0 }
{
}
