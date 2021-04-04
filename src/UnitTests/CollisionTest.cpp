#include "Collision.hpp"
#include "Shape.hpp"
#include "gtest/gtest.h"
#include <utility>

using jt::Collision;
using jt::Shape;

namespace {
jt::Shape makeShape(float sx, float sy, float px, float py)
{
    Shape s {};
    s.makeRect({ sx, sy });
    s.setPosition({ px, py });
    s.update(0.0f);
    return s;
}

std::shared_ptr<Shape> const makeShapePtr(float sx, float sy, float px, float py)
{
    return std::make_shared<Shape>(makeShape(sx, sy, px, py));
}

} // namespace

TEST(CollisionTestCircle, ShapePtrNoOverlap)
{
    auto const s1 = makeShapePtr(20.0f, 20.0f, 0.0f, 0.0f);
    auto const s2 = makeShapePtr(20.0f, 20.0f, 100.0f, 100.0f);

    EXPECT_FALSE(Collision::CircleTest(s1, s2));
}

TEST(CollisionTestCircle, ShapePtrOverlap)
{
    auto const s1 = makeShapePtr(20.0f, 20.0f, 0.0f, 0.0f);
    auto const s2 = makeShapePtr(20.0f, 20.0f, 10.0f, 10.0f);

    EXPECT_TRUE(Collision::CircleTest(s1, s2));
}

TEST(CollisionTestCircle, ShapePtrSelf)
{
    auto const s1 = makeShapePtr(20.0f, 20.0f, 0.0f, 0.0f);

    EXPECT_TRUE(Collision::CircleTest(s1, s1));
}

TEST(CollisionTestCircle, ShapeNoOverlap)
{
    auto const s1 = makeShape(20.0f, 20.0f, 0.0f, 0.0f);
    auto const s2 = makeShape(20.0f, 20.0f, 100.0f, 100.0f);

    EXPECT_FALSE(Collision::CircleTest(s1, s2));
}

TEST(CollisionTestCircle, ShapeOverlap)
{
    auto const s1 = makeShape(20.0f, 20.0f, 0.0f, 0.0f);
    auto const s2 = makeShape(20.0f, 20.0f, 10.0f, 10.0f);

    EXPECT_TRUE(Collision::CircleTest(s1, s2));
}

TEST(CollisionTestCircle, ShapeSelf)
{
    auto const s1 = makeShape(20.0f, 20.0f, 20.0f, 20.0f);

    EXPECT_TRUE(Collision::CircleTest(s1, s1));
}
