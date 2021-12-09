#include "math_helper.hpp"
#include "vector.hpp"
#include "gtest/gtest.h"

using namespace jt::MathHelper;
using v = jt::Vector2f;

TEST(VectorBetween, SingleValue)
{
    int const lower { 4 };
    int const upper { lower };
    auto const result = numbersBetween(lower, upper);
    ASSERT_EQ(result.size(), upper - lower + 1);
    ASSERT_EQ(result.at(0), 4);
}

TEST(VectorBetween, Range)
{
    int const lower { -2 };
    int const upper { 3 };
    auto const result = numbersBetween(lower, upper);
    ASSERT_EQ(result.size(), upper - lower + 1);
    ASSERT_EQ(result.at(0), -2);
    ASSERT_EQ(result.at(1), -1);
    ASSERT_EQ(result.at(5), 3);
}

TEST(VectorBetween, Inverted)
{
    int const lower { 4 };
    int const upper { 3 };
    auto const result = numbersBetween(lower, upper);
    ASSERT_EQ(result.size(), lower - upper + 1);
    ASSERT_EQ(result.at(0), 3);
    ASSERT_EQ(result.at(1), 4);
}

TEST(VectorLengthTest, LengthOfVectorZero)
{
    jt::Vector2f const v0 { 0.0f, 0.0f };
    float const l { 0.0f };
    ASSERT_EQ(length(v0), l);
    ASSERT_EQ(lengthSquared(v0), l);
}

TEST(VectorLengthTest, LengthOfVectorOneDimension)
{
    jt::Vector2f const v0 { 0.0f, 10 };
    float const l { 10.0f };
    ASSERT_EQ(length(v0), l);
    ASSERT_EQ(lengthSquared(v0), l * l);
}

TEST(VectorLengthTest, LengthOfVectorTwoDimensions)
{
    jt::Vector2f const v0 { -10, 10 };
    float const l { 14.14213562373095048802f };
    ASSERT_NEAR(length(v0), l, 0.005);
    ASSERT_NEAR(lengthSquared(v0), l * l, 0.005);
}

TEST(VectorNoralize, NormalizeOfNormalizedVector)
{
    jt::Vector2f v0 { 1, 0 };
    jt::Vector2f const cv0 { v0 };
    normalizeMe(v0);

    ASSERT_EQ(v0, cv0);
}

TEST(VectorNoralize, NormalizeOfVector)
{
    jt::Vector2f v0 { 15.4f, -42.22f };
    normalizeMe(v0);

    ASSERT_EQ(length(v0), 1.0f);
}

TEST(VectorNoralize, NormalizeOfZeroVector)
{
    jt::Vector2f v0 { 0.0f, 0.0f };
    ASSERT_NO_THROW(normalizeMe(v0));
    ASSERT_EQ(v0.x, 0.0f);
    ASSERT_EQ(v0.y, 0.0f);
}

TEST(Rad2DegConversion, Inverse)
{
    float const v { 0.25f };
    ASSERT_NEAR(v, rad2deg(deg2rad(v)), 0.0001f);
}

class RotateByTestFixture : public ::testing::TestWithParam<jt::Vector2f> {
};

INSTANTIATE_TEST_SUITE_P(RotateByTest, RotateByTestFixture,
    ::testing::Values(jt::Vector2f { 1.0f, 0.0f }, jt::Vector2f { 0.0f, 1.0f },
        jt::Vector2f { 1000.0f, 0.0f }, jt::Vector2f { 0.0f, 1000.0f },
        jt::Vector2f { -3.0f, 5.22222f }));

TEST_P(RotateByTestFixture, FullThreeHundretSixty)
{
    float const angle = 360.0f;
    auto const initial { GetParam() };
    auto const rotated = rotateBy(initial, angle);
    ASSERT_NEAR(initial.x, rotated.x, 0.001f);
    ASSERT_NEAR(initial.y, rotated.y, 0.001f);
}

TEST_P(RotateByTestFixture, MinusFullThreeHundretSixtyDegree)
{
    float const angle = -360.0f;
    auto const initial { GetParam() };
    auto const rotated = rotateBy(initial, angle);
    ASSERT_NEAR(initial.x, rotated.x, 0.001f);
    ASSERT_NEAR(initial.y, rotated.y, 0.001f);
}

TEST(RotateByTestFixture, NinetyDegree)
{
    float const angle { 90.0f };
    jt::Vector2f const initial1 { 1.0, 0.0f };
    jt::Vector2f const initial2 { 0.0, 1.0f };
    jt::Vector2f const initial3 { -1.0, 0.0f };
    jt::Vector2f const initial4 { 0.0, -1.0f };

    auto const rotated1 = rotateBy(initial1, angle);
    auto const rotated2 = rotateBy(initial2, angle);
    auto const rotated3 = rotateBy(initial3, angle);
    auto const rotated4 = rotateBy(initial4, angle);

    ASSERT_NEAR(initial2.x, rotated1.x, 0.001f);
    ASSERT_NEAR(initial2.y, rotated1.y, 0.001f);

    ASSERT_NEAR(initial3.x, rotated2.x, 0.001f);
    ASSERT_NEAR(initial3.y, rotated2.y, 0.001f);

    ASSERT_NEAR(initial4.x, rotated3.x, 0.001f);
    ASSERT_NEAR(initial4.y, rotated3.y, 0.001f);

    ASSERT_NEAR(initial1.x, rotated4.x, 0.001f);
    ASSERT_NEAR(initial1.y, rotated4.y, 0.001f);
}

TEST(RotateByTestFixture, MinusNinetyDegree)
{
    float const angle { -90.0f };
    jt::Vector2f const initial1 { 1.0, 0.0f };
    jt::Vector2f const initial2 { 0.0, 1.0f };
    jt::Vector2f const initial3 { -1.0, 0.0f };
    jt::Vector2f const initial4 { 0.0, -1.0f };

    auto const rotated1 = rotateBy(initial1, angle);
    auto const rotated2 = rotateBy(initial2, angle);
    auto const rotated3 = rotateBy(initial3, angle);
    auto const rotated4 = rotateBy(initial4, angle);

    ASSERT_NEAR(initial4.x, rotated1.x, 0.001f);
    ASSERT_NEAR(initial4.y, rotated1.y, 0.001f);

    ASSERT_NEAR(initial1.x, rotated2.x, 0.001f);
    ASSERT_NEAR(initial1.y, rotated2.y, 0.001f);

    ASSERT_NEAR(initial2.x, rotated3.x, 0.001f);
    ASSERT_NEAR(initial2.y, rotated3.y, 0.001f);

    ASSERT_NEAR(initial3.x, rotated4.x, 0.001f);
    ASSERT_NEAR(initial3.y, rotated4.y, 0.001f);
}

TEST(ClampTest, working)
{
    float const in { 0.5f };
    float const out = clamp(in, 0.0f, 1.0f);
    ASSERT_EQ(in, out);
}

TEST(ClampTest, lower)
{
    float const in { -0.5f };
    float const lower { 0.0f };
    float const out = clamp(in, lower, 1.0f);
    ASSERT_EQ(lower, out);
}

TEST(ClampTest, upper)
{
    float const in { 2.5f };
    float const upper { 2.2f };
    float const out = clamp(in, 0.0f, upper);
    ASSERT_EQ(upper, out);
}

TEST(FloatToString, ValidEntryZero)
{
    float const f { 0.0f };
    ASSERT_EQ(floatToStringWithXDigits(f, 1), "0.0");
    ASSERT_EQ(floatToStringWithXDigits(f, 2), "0.00");
    ASSERT_EQ(floatToStringWithXDigits(f, 3), "0.000");
    ASSERT_EQ(floatToStringWithXDigits(f, 4), "0.0000");
}

TEST(FloatToString, CorrectRounding)
{
    float const f { 1.8f };
    ASSERT_EQ(floatToStringWithXDigits(f, 0), "2");
}

TEST(FloatToString, ValidEntry)
{
    float const f { 1.23456f };
    ASSERT_EQ(floatToStringWithXDigits(f, 1), "1.2");
    ASSERT_EQ(floatToStringWithXDigits(f, 2), "1.23");
    ASSERT_EQ(floatToStringWithXDigits(f, 3), "1.235");
    ASSERT_EQ(floatToStringWithXDigits(f, 4), "1.2346");
}

TEST(FloatToString, StringWithLengthZero)
{
    float const f { 1.23456f };
    ASSERT_EQ(floatToStringWithXDigits(f, 0), "1");
}

TEST(AngleOf, Horizontal)
{
    jt::Vector2f const vec { 1.0f, 0.0f };
    ASSERT_EQ(angleOf(vec), 0.0f);
}

TEST(AngleOf, HorizontalNegative)
{
    jt::Vector2f const vec { -10.0f, .0f };
    ASSERT_EQ(angleOf(vec), -180.0f);
}

TEST(AngleOf, Vertical)
{
    jt::Vector2f const vec { 0.0f, 1.0f };
    ASSERT_EQ(angleOf(vec), -90.0f);
}

TEST(AngleOf, VerticalNegative)
{
    jt::Vector2f const vec { 0.0f, 1.0f };
    ASSERT_EQ(angleOf(vec), -90.0f);
}
