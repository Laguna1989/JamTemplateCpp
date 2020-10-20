
#include "../JamTemplate/MathHelper.hpp"
#include "gtest/gtest.h"

using namespace JamTemplate::MathHelper;
using v = sf::Vector2f;

TEST(VectorBetween, Single)
{
    int const lower { 4 };
    int const upper { lower };
    auto const result = vectorBetween(lower, upper);
    EXPECT_EQ(result.size(), upper - lower + 1);
    EXPECT_EQ(result.at(0), 4);
}

TEST(VectorBetween, Range)
{
    int const lower { -2 };
    int const upper { 3 };
    auto const result = vectorBetween(lower, upper);
    EXPECT_EQ(result.size(), upper - lower + 1);
    EXPECT_EQ(result.at(0), -2);
    EXPECT_EQ(result.at(1), -1);
    EXPECT_EQ(result.at(5), 3);
}

TEST(VectorBetween, Inverted)
{
    int const lower { 4 };
    int const upper { 3 };
    auto const result = vectorBetween(lower, upper);
    EXPECT_EQ(result.size(), lower - upper + 1);
    EXPECT_EQ(result.at(0), 3);
    EXPECT_EQ(result.at(1), 4);
}

TEST(VectorLengthTest, LengthOfVectorZero)
{
    sf::Vector2f const v0 { 0.0f, 0.0f };
    float const l { 0.0f };
    EXPECT_EQ(length(v0), l);
    EXPECT_EQ(lengthSquared(v0), l);
}

TEST(VectorLengthTest, LengthOfVectorOneDimension)
{
    sf::Vector2f const v0 { 0.0f, 10 };
    float const l { 10.0f };
    EXPECT_EQ(length(v0), l);
    EXPECT_EQ(lengthSquared(v0), l * l);
}

TEST(VectorLengthTest, LengthOfVectorTwoDimensions)
{
    sf::Vector2f const v0 { -10, 10 };
    float const l { 14.14213562373095048802f };
    EXPECT_NEAR(length(v0), l, 0.005);
    EXPECT_NEAR(lengthSquared(v0), l * l, 0.005);
}

TEST(VectorNoralize, NormalizeOfNormalizedVector)
{
    sf::Vector2f v0 { 1, 0 };
    sf::Vector2f const cv0 { v0 };
    normalizeMe(v0);

    EXPECT_EQ(v0, cv0);
}

TEST(VectorNoralize, NormalizeOfVector)
{
    sf::Vector2f v0 { 15.4f, -42.22f };
    normalizeMe(v0);

    EXPECT_EQ(length(v0), 1.0f);
}

TEST(VectorNoralize, NormalizeOfZeroVector)
{
    sf::Vector2f v0 { 0.0f, 0.0f };
    EXPECT_NO_THROW(normalizeMe(v0));
    EXPECT_EQ(v0.x, 0.0f);
    EXPECT_EQ(v0.y, 0.0f);
}

TEST(Rad2DegConversion, Inverse)
{
    float const v { 0.25f };
    EXPECT_NEAR(v, rad2deg(deg2rad(v)), 0.0001f);
}

TEST(ClampTest, working)
{
    float const in { 0.5f };
    float const out = clamp(in, 0.0f, 1.0f);
    EXPECT_EQ(in, out);
}

TEST(ClampTest, lower)
{
    float const in { -0.5f };
    float const lower { 0.0f };
    float const out = clamp(in, lower, 1.0f);
    EXPECT_EQ(lower, out);
}

TEST(ClampTest, upper)
{
    float const in { 2.5f };
    float const upper { 2.2f };
    float const out = clamp(in, 0.0f, upper);
    EXPECT_EQ(upper, out);
}
