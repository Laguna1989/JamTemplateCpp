#ifndef GUARD_JAMTEMPLATE_RECT_BASE_GUARD_HPP_12345
#define GUARD_JAMTEMPLATE_RECT_BASE_GUARD_HPP_12345

#include "rect_base.hpp"

namespace jt {
class rectBase {
public:
    virtual float left() const = 0;
    virtual float top() const = 0;
    virtual float width() const = 0;
    virtual float height() const = 0;

    virtual float& left() = 0;
    virtual float& top() = 0;
    virtual float& width() = 0;
    virtual float& height() = 0;
};

class rectiBase {
public:
    virtual int left() const = 0;
    virtual int top() const = 0;
    virtual int width() const = 0;
    virtual int height() const = 0;

    virtual int& left() = 0;
    virtual int& top() = 0;
    virtual int& width() = 0;
    virtual int& height() = 0;
};

} // namespace jt
#endif
