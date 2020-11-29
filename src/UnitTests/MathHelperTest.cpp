#include "MathHelper.hpp"
#include "vector.hpp"
#include "gtest/gtest.h"

using namespace jt::MathHelper;
using v = jt::vector2;

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
    jt::vector2 const v0 { 0.0f, 0.0f };
    float const l { 0.0f };
    EXPECT_EQ(length(v0), l);
    EXPECT_EQ(lengthSquared(v0), l);
}

TEST(VectorLengthTest, LengthOfVectorOneDimension)
{
    jt::vector2 const v0 { 0.0f, 10 };
    float const l { 10.0f };
    EXPECT_EQ(length(v0), l);
    EXPECT_EQ(lengthSquared(v0), l * l);
}

TEST(VectorLengthTest, LengthOfVectorTwoDimensions)
{
    jt::vector2 const v0 { -10, 10 };
    float const l { 14.14213562373095048802f };
    EXPECT_NEAR(length(v0), l, 0.005);
    EXPECT_NEAR(lengthSquared(v0), l * l, 0.005);
}

TEST(VectorNoralize, NormalizeOfNormalizedVector)
{
    jt::vector2 v0 { 1, 0 };
    jt::vector2 const cv0 { v0 };
    normalizeMe(v0);

    EXPECT_EQ(v0, cv0);
}

TEST(VectorNoralize, NormalizeOfVector)
{
    jt::vector2 v0 { 15.4f, -42.22f };
    normalizeMe(v0);

    EXPECT_EQ(length(v0), 1.0f);
}

TEST(VectorNoralize, NormalizeOfZeroVector)
{
    jt::vector2 v0 { 0.0f, 0.0f };
    EXPECT_NO_THROW(normalizeMe(v0));
    EXPECT_EQ(v0.x(), 0.0f);
    EXPECT_EQ(v0.y(), 0.0f);
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

TEST(FloatToString, ValidEntryZero)
{
    float const f { 0.0f };
    EXPECT_EQ(floatToStringWithXDigits(f, 1), "0.0");
    EXPECT_EQ(floatToStringWithXDigits(f, 2), "0.00");
    EXPECT_EQ(floatToStringWithXDigits(f, 3), "0.000");
    EXPECT_EQ(floatToStringWithXDigits(f, 4), "0.0000");
}

TEST(FloatToString, CorrectRounding)
{
    float const f { 1.8f };
    EXPECT_EQ(floatToStringWithXDigits(f, 0), "2");
}

TEST(FloatToString, ValidEntry)
{
    float const f { 1.23456f };
    EXPECT_EQ(floatToStringWithXDigits(f, 1), "1.2");
    EXPECT_EQ(floatToStringWithXDigits(f, 2), "1.23");
    EXPECT_EQ(floatToStringWithXDigits(f, 3), "1.235");
    EXPECT_EQ(floatToStringWithXDigits(f, 4), "1.2346");
}

TEST(FloatToString, StringWithLengthZero)
{
    float const f { 1.23456f };
    EXPECT_EQ(floatToStringWithXDigits(f, 0), "1");
}
