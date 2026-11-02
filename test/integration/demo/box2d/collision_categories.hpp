#ifndef JAMTEMPLATE_COLLISION_CATEGORIES_HPP
#define JAMTEMPLATE_COLLISION_CATEGORIES_HPP

#include <box2d/box2d.h>
#include <cstdint>

/// Box2D collision categories, used as b2Filter::categoryBits to tag what a shape is.
/// The default mask bits collide with all categories, so tagging alone does not change collisions.
enum CollisionCategory : std::uint64_t {
    eCategoryGround = B2_DEFAULT_CATEGORY_BITS,
    eCategoryPlayer = 0x2,
    eCategoryEnemy = 0x4,
};

#endif // JAMTEMPLATE_COLLISION_CATEGORIES_HPP
