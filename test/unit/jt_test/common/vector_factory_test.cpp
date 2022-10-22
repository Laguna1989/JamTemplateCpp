#include <vector_factory.hpp>
#include <gtest/gtest.h>

TEST(VectorFactoryTest, CreateZeroVector)
{
    jt::Vector2f const expected { 0.0f, 0.0f };
    ASSERT_EQ(jt::VectorFactory::zero(), expected);
}

TEST(VectorFactoryTest, Cartesian)
{
    auto const x = 12.0f;
    auto const y = -2.5f;
    auto expected = jt::Vector2f { x, y };
    ASSERT_EQ(jt::VectorFactory::fromCartesian(x, y), expected);
}

TEST(VectorFactoryTest, Polar)
{
    auto const r = 12.0f;
    auto const phi = 90.0f;
    auto expected = jt::Vector2f { 0.0f, 12.0f };
    auto const vec = jt::VectorFactory::fromPolar(r, phi);
    ASSERT_NEAR(vec.x, expected.x, 1e-6);
    ASSERT_NEAR(vec.y, expected.y, 1e-6);
}
