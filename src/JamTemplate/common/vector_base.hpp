#ifndef GUARD_JAMTEMPLATE_VECTOR_BASE_GUARD_HPP_12345
#define GUARD_JAMTEMPLATE_VECTOR_BASE_GUARD_HPP_12345

#include "vector_base.hpp"

/*
This file only has the interface contract for the vector classes to be implemented
by the different libs. The interface is conveyed through the
*/

namespace jt {

class vector2Base {
public:
    virtual float x() const = 0;
    virtual float y() const = 0;

    virtual float& y() = 0;
    virtual float& x() = 0;
};

class vector2uBase {
public:
    virtual unsigned int x() const = 0;
    virtual unsigned int y() const = 0;

    virtual unsigned int& x() = 0;
    virtual unsigned int& y() = 0;
};

} // namespace jt

#endif
