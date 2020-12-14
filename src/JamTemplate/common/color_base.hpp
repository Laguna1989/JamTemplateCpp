#ifndef GUARD_JAMTEMPLATE_COLOR_BASE_GUARD_HPP_12345
#define GUARD_JAMTEMPLATE_COLOR_BASE_GUARD_HPP_12345

#include <cstdint>

namespace jt {

class ColorBase {
    virtual std::uint8_t r() const = 0;
    virtual std::uint8_t g() const = 0;
    virtual std::uint8_t b() const = 0;
    virtual std::uint8_t a() const = 0;
    virtual std::uint8_t& r() = 0;
    virtual std::uint8_t& g() = 0;
    virtual std::uint8_t& b() = 0;
    virtual std::uint8_t& a() = 0;
};

} // namespace jt

#endif
