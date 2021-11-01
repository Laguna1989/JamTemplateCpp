#ifndef GUARD_JAMTEMPLATE_RECT_BASE_GUARD_HPP_12345
#define GUARD_JAMTEMPLATE_RECT_BASE_GUARD_HPP_12345

/*
This file only has the interface contract for the rect classes to be implemented
by the different libs. The interface is conveyed through the
*/

namespace jt {
class rectBase {
public:
    /// Get left of rect
    /// \return left value
    virtual float left() const = 0;

    /// top of rect
    /// \return top value
    virtual float top() const = 0;

    /// width of rect
    /// \return width value
    virtual float width() const = 0;

    /// height of rect
    /// \return height value
    virtual float height() const = 0;

    /// Get left of rect
    /// \return left value
    virtual float& left() = 0;

    /// top of rect
    /// \return top value
    virtual float& top() = 0;

    /// width of rect
    /// \return width value
    virtual float& width() = 0;

    /// height of rect
    /// \return height value
    virtual float& height() = 0;
};

class rectiBase {
public:
    /// Get left of rect
    /// \return left value
    virtual int left() const = 0;

    /// top of rect
    /// \return top value
    virtual int top() const = 0;

    /// width of rect
    /// \return width value
    virtual int width() const = 0;

    /// height of rect
    /// \return height value
    virtual int height() const = 0;

    /// Get left of rect
    /// \return left value
    virtual int& left() = 0;

    /// top of rect
    /// \return top value
    virtual int& top() = 0;

    /// width of rect
    /// \return width value
    virtual int& width() = 0;

    /// height of rect
    /// \return height value
    virtual int& height() = 0;
};

} // namespace jt
#endif
