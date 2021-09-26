#ifndef GUARD_JAMTEMPLATE_LINTERP_HPP_INCLUDEGUARD
#define GUARD_JAMTEMPLATE_LINTERP_HPP_INCLUDEGUARD

#include <assert.h>

namespace jt {

template <typename T>
static T precheck(T const& ti)
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

// linear interpolation between values a and b with t between 0 and 1
template <typename T>
static T linear(T const& a, T const& b, T const& ti)
{
    auto t = precheck(ti);
    return (1.0f - t) * a + t * b;
}

} // namespace Lerp
} // namespace jt

#endif // GUARD_JAMTEMPLATE_LINTERP_HPP_INCLUDEGUARD
