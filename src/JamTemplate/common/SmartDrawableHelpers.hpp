#ifndef GUARD_JAMTEMPLATE_SMART_DRAWABLES_HELPER_GUARD_HPP_12345
#define GUARD_JAMTEMPLATE_SMART_DRAWABLES_HELPER_GUARD_HPP_12345

#include "Color.hpp"
#include "Vector.hpp"
#include <memory>

namespace jt {

// fwd declarations
class SmartShape;

namespace sdh {

std::shared_ptr<jt::SmartShape> createRectShape(
    jt::Vector2 size, jt::Color const& col = jt::colors::White);

} // namespace sdh

} // namespace jt

#endif
