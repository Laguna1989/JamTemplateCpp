#include "collision.hpp"
#include "sdl_setup.hpp"
#include "shape.hpp"
#include "texture_manager_impl.hpp"
#include "gtest/gtest.h"

using jt::Collision;
using jt::Shape;

namespace {
jt::Shape makeShape(
    float sx, float sy, float px, float py, jt::TextureManagerInterface& textureManager)
{
    Shape s {};
    s.makeRect(jt::Vector2f { sx, sy }, textureManager);
    s.setPosition(jt::Vector2f { px, py });
    // note: by default the top left corner of the shape is the origin. This needs to be corrected
    // here, so the center of the shape is used.
    s.setOffset(jt::Vector2f { -sx / 2.0f, -sy / 2.0f });
    s.update(0.0f);
    return s;
}

std::shared_ptr<Shape> const makeShapePtr(float sx, float sy, float px, float py)
{
    return std::make_shared<Shape>(makeShape(sx, sy, px, py, getTextureManager()));
}

} // namespace

class CollisionCircleNoOverlapPositionParametrizedTestFixture
    : public ::testing::TestWithParam<std::pair<std::shared_ptr<Shape>, std::shared_ptr<Shape>>> {
};

TEST_P(CollisionCircleNoOverlapPositionParametrizedTestFixture, ShapePtrNoOverlap)
{
    auto const s1 = std::get<0>(GetParam());
    auto const s2 = std::get<1>(GetParam());

    ASSERT_FALSE(Collision::CircleTest(s1, s2));
}

INSTANTIATE_TEST_SUITE_P(CollisionCircleNoOverlapPositionParametrizedTest,
    CollisionCircleNoOverlapPositionParametrizedTestFixture,
    ::testing::Values(
        std::make_pair(makeShapePtr(1.0f, 1.0f, 0.0f, 0.0f), makeShapePtr(1.0f, 1.0f, 1.0f, 1.0f)),
        std::make_pair(makeShapePtr(1.0f, 1.0f, 1.0f, 1.0f), makeShapePtr(1.0f, 1.0f, 0.0f, 0.0f)),
        std::make_pair(makeShapePtr(1.0f, 1.0f, 0.0f, 0.0f), makeShapePtr(1.0f, 1.0f, 1.0f, 0.0f)),
        std::make_pair(makeShapePtr(1.0f, 1.0f, 0.0f, 0.0f), makeShapePtr(1.0f, 1.0f, 0.0f, 1.0f)),
        std::make_pair(
            makeShapePtr(99.0f, 99.0f, 0.0f, 0.0f), makeShapePtr(20.0f, 20.0f, 100.0f, 100.0f)),
        std::make_pair(
            makeShapePtr(20.0f, 20.0f, 0.0f, 0.0f), makeShapePtr(20.0f, 20.0f, 100.0f, 100.0f))));

class CollisionCircleOverlapPositionParametrizedTestFixture
    : public ::testing::TestWithParam<std::pair<std::shared_ptr<Shape>, std::shared_ptr<Shape>>> {
};

TEST_P(CollisionCircleOverlapPositionParametrizedTestFixture, ShapePtrOverlap)
{
    auto const s1 = std::get<0>(GetParam());
    auto const s2 = std::get<1>(GetParam());

    ASSERT_TRUE(Collision::CircleTest(s1, s2));
}

INSTANTIATE_TEST_SUITE_P(CollisionCircleOverlapPositionParametrizedTest,
    CollisionCircleOverlapPositionParametrizedTestFixture,
    ::testing::Values(
        std::make_pair(makeShapePtr(1.0f, 1.0f, 0.0f, 0.0f), makeShapePtr(1.0f, 1.0f, 0.0f, 0.0f)),
        std::make_pair(makeShapePtr(1.0f, 1.0f, 0.0f, 0.0f), makeShapePtr(1.0f, 1.0f, 0.5f, 0.0f)),
        std::make_pair(makeShapePtr(1.0f, 1.0f, 0.0f, 0.0f), makeShapePtr(1.0f, 1.0f, 0.0f, 0.5f)),
        std::make_pair(makeShapePtr(1.0f, 1.0f, 0.0f, 0.0f), makeShapePtr(1.0f, 1.0f, 0.5f, 0.5f)),
        std::make_pair(makeShapePtr(1.0f, 1.0f, 0.0f, 0.0f), makeShapePtr(1.0f, 1.0f, 0.9f, 0.0f)),
        std::make_pair(makeShapePtr(1.0f, 1.0f, 0.0f, 0.0f), makeShapePtr(1.0f, 1.0f, 0.0f, 0.9f)),
        std::make_pair(
            makeShapePtr(100.0f, 100.0f, 0.0f, 0.0f), makeShapePtr(100.0f, 100.0f, 0.0f, 0.0f)),
        std::make_pair(
            makeShapePtr(1.0f, 1.0f, 0.0f, 0.0f), makeShapePtr(100.0f, 100.0f, 0.0f, 0.0f)),
        std::make_pair(
            makeShapePtr(1.0f, 1.0f, 4.0f, 0.0f), makeShapePtr(10.0f, 10.0f, 0.0f, 0.0f)),
        std::make_pair(
            makeShapePtr(1.0f, 1.0f, 0.0f, 4.0f), makeShapePtr(10.0f, 10.0f, 0.0f, 0.0f))));

TEST(CollisionTestCircle, ShapePtrSelf)
{
    auto const s1 = makeShapePtr(20.0f, 20.0f, 0.0f, 0.0f);

    ASSERT_TRUE(Collision::CircleTest(s1, s1));
}

TEST(CollisionTestCircle, ShapeNoOverlap)
{
    auto const s1 = makeShape(20.0f, 20.0f, 0.0f, 0.0f, getTextureManager());
    auto const s2 = makeShape(20.0f, 20.0f, 100.0f, 100.0f, getTextureManager());

    ASSERT_FALSE(Collision::CircleTest(s1, s2));
}

TEST(CollisionTestCircle, ShapeOverlap)
{
    auto const s1 = makeShape(20.0f, 20.0f, 0.0f, 0.0f, getTextureManager());
    auto const s2 = makeShape(20.0f, 20.0f, 10.0f, 10.0f, getTextureManager());

    ASSERT_TRUE(Collision::CircleTest(s1, s2));
}

TEST(CollisionTestCircle, ShapeSelf)
{
    auto const s1 = makeShape(20.0f, 20.0f, 20.0f, 20.0f, getTextureManager());

    ASSERT_TRUE(Collision::CircleTest(s1, s1));
}
