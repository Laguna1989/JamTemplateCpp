#include "box2d_helpers.hpp"

bool jt::Box2DHelpers::isCategoryPair(
    b2ShapeId const shape1, b2ShapeId const shape2, std::uint64_t const a, std::uint64_t const b)
{
    auto const category1 = b2Shape_GetFilter(shape1).categoryBits;
    auto const category2 = b2Shape_GetFilter(shape2).categoryBits;
    return ((category1 & a) != 0 && (category2 & b) != 0)
        || ((category1 & b) != 0 && (category2 & a) != 0);
}
