#pragma once

#include <box2d/box2d.h>
#include <cstdint>

namespace jt {

namespace Box2DHelpers {

/// Check if one shape belongs to category a and the other one to category b, in any order.
/// \param shape1 first shape, e.g. b2ContactBeginTouchEvent::shapeIdA
/// \param shape2 second shape, e.g. b2ContactBeginTouchEvent::shapeIdB
/// \param a category bits to match for one of the shapes
/// \param b category bits to match for the other shape
/// \return true if the shapes match the categories
bool isCategoryPair(b2ShapeId shape1, b2ShapeId shape2, std::uint64_t a, std::uint64_t b);

} // namespace Box2DHelpers

} // namespace jt
