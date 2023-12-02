#ifndef JAMTEMPLATE_LINTERP_HPP
#define JAMTEMPLATE_LINTERP_HPP

#include <assert.h>
#include <cmath>

namespace jt {

template <typename T>
static T precheck(T const& ti) noexcept
{
    T t = ti;
    if (t < 0) {
        t = 0;
    }
    if (t > 1) {
        t = 1;
    }
    assert(t >= 0.0 && t <= 1.0);
    return t;
}

namespace Lerp {

/// linear interpolation between values a and b with t between 0 and 1
template <typename T>
[[deprecated("use std::lerp instead")]] static T linear(T const& a, T const& b, T const& ti)
{
    auto const t = precheck(ti);
    return std::lerp(a, b, t);
}

} // namespace Lerp
} // namespace jt

#endif // JAMTEMPLATE_LINTERP_HPP
