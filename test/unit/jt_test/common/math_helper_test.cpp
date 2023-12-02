#include <math_helper.hpp>
#include <vector.hpp>
#include <complex>
#include <gtest/gtest.h>

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

TEST(FastSqrtTest, QsqrtTest)
{
    ASSERT_NEAR(jt::MathHelper::qrsqrt(2.0f) * 2.0f, 1.41421356f, 0.01f);
    ASSERT_NEAR(jt::MathHelper::qsqrt(20.0f), std::sqrt(20.0f), 0.01f);
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
    ASSERT_NEAR(length(v0), l, 0.1f);
    ASSERT_NEAR(lengthSquared(v0), l * l, 0.1f);
}

TEST(VectorLengthTest, LengthOfVectorTwoDimensions)
{
    jt::Vector2f const v0 { -10, 10 };
    float const l { 14.14213562373095048802f };
    ASSERT_NEAR(length(v0), l, 0.1f);
    ASSERT_NEAR(lengthSquared(v0), l * l, 0.1f);
}

TEST(DistanceBetweenTest, DistanceBetweenTwoVectorsOnlyX)
{
    jt::Vector2f const a { 10.0f, 0.0f };
    jt::Vector2f const b { 20.0f, 0.0f };
    float const expectedLength { 10.0f };
    ASSERT_NEAR(distanceBetween(a, b), expectedLength, 0.1f);
}

TEST(DistanceBetweenTest, DistanceBetweenTwoVectorsOnlyY)
{
    jt::Vector2f const a { 0.0f, -10.0f };
    jt::Vector2f const b { 0.0f, 35.0f };
    float const expectedLength { 45.0f };
    ASSERT_NEAR(distanceBetween(a, b), expectedLength, 0.1f);
}

TEST(DistanceBetweenTest, DistanceBetweenTwoVectorsBothDimensions)
{
    jt::Vector2f const a { 1.0f, 1.0f };
    jt::Vector2f const b { 0.0f, 2.0f };
    float const expectedLength { 1.41421f };
    ASSERT_NEAR(distanceBetween(a, b), expectedLength, 0.0005f);
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

TEST(Rad2DegConversion, Rad2DegAndDegToRadCancelEachOther)
{
    std::vector<float> const values { 0.25f, 1.0f, 2.0f, 5.0f, 10.0f, 20.0f, 45.0f, 90.0f, 180.0f,
        360.0f };
    for (auto const& v : values) {
        ASSERT_NEAR(v, rad2deg(deg2rad(v)), 0.0001f);
    }
}

class RotateByTestFixture : public ::testing::TestWithParam<jt::Vector2f> { };

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

TEST(ClampVectorTest, inside)
{
    jt::Vector2f const in { 0.5f, 0.5f };
    auto const out = clamp(in, jt::Vector2f { 0.0f, 0.0f }, jt::Vector2f { 1.0f, 1.0f });
    ASSERT_EQ(in, out);
}

TEST(ClampVectorTest, lowerX)
{
    jt::Vector2f const in { -0.5f, 0.5f };
    float const lower { 0.0f };
    auto const out = clamp(in, jt::Vector2f { lower, lower }, jt::Vector2f { 1.0f, 1.0f });
    ASSERT_EQ(lower, out.x);
    ASSERT_EQ(0.5f, out.y);
}

TEST(ClampVectorTest, lowerY)
{
    jt::Vector2f const in { 0.5f, -9999.9f };
    float const lower { 0.0f };
    auto const out = clamp(in, jt::Vector2f { lower, lower }, jt::Vector2f { 1.0f, 1.0f });
    ASSERT_EQ(0.5f, out.x);
    ASSERT_EQ(lower, out.y);
}

TEST(ClampVectorTest, upperX)
{
    jt::Vector2f const in { 2.5f, 0.5f };
    float const upper { 2.2f };
    auto const out = clamp(in, jt::Vector2f { 0.0f, 0.0f }, jt::Vector2f { upper, upper });
    ASSERT_EQ(upper, out.x);
    ASSERT_EQ(0.5f, out.y);
}

TEST(ClampVectorTest, upperY)
{
    jt::Vector2f const in { 0.5f, 9999.9f };
    float const upper { 2.2f };
    auto const out = clamp(in, jt::Vector2f { 0.0f, 0.0f }, jt::Vector2f { upper, upper });
    ASSERT_EQ(0.5f, out.x);
    ASSERT_EQ(upper, out.y);
}

TEST(FloatToString, ValidEntryZero)
{
    float const f { 0.0f };
    ASSERT_EQ(floatToStringWithXDecimalDigits(f, 1), "0.0");
    ASSERT_EQ(floatToStringWithXDecimalDigits(f, 2), "0.00");
    ASSERT_EQ(floatToStringWithXDecimalDigits(f, 3), "0.000");
    ASSERT_EQ(floatToStringWithXDecimalDigits(f, 4), "0.0000");
}

TEST(FloatToString, CorrectRounding)
{
    float const f { 1.8f };
    ASSERT_EQ(floatToStringWithXDecimalDigits(f, 0), "2");
}

TEST(FloatToString, ValidEntry)
{
    float const f { 1.23456f };
    ASSERT_EQ(floatToStringWithXDecimalDigits(f, 1), "1.2");
    ASSERT_EQ(floatToStringWithXDecimalDigits(f, 2), "1.23");
    ASSERT_EQ(floatToStringWithXDecimalDigits(f, 3), "1.235");
    ASSERT_EQ(floatToStringWithXDecimalDigits(f, 4), "1.2346");
}

TEST(FloatToString, StringWithLengthZero)
{
    float const f { 1.23456f };
    ASSERT_EQ(floatToStringWithXDecimalDigits(f, 0), "1");
}

TEST(IsPowerOfTwo, ReturnsTrueForPowersOfTwo)
{
    for (auto v : { 1u, 2u, 4u, 8u, 16u, 32u, 64u, 128u, 256u, 512u }) {
        ASSERT_TRUE(isPowerOfTwo(v));
    }
}

TEST(IsPowerOfTwo, ReturnsFalseForNonPowersOfTwo)
{
    for (auto v : { 3u, 5u, 13u, 31u, 33u, 42u, 65u, 120u, 1337u }) {
        std::cout << v << std::endl;
        ASSERT_FALSE(isPowerOfTwo(v));
    }
}

TEST(IsPowerOfTwo, ReturnsFalseForZero) { ASSERT_FALSE(isPowerOfTwo(0u)); }

TEST(AngleOf, Horizontal)
{
    jt::Vector2f const vec { 1.0f, 0.0f };
    ASSERT_EQ(angleOf(vec), 0.0f);
}

TEST(AngleOf, HorizontalNegative)
{
    jt::Vector2f const vec { -10.0f, .0f };
    ASSERT_FLOAT_EQ(angleOf(vec), -180.0f);
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

TEST(Dot, SameVector)
{
    jt::Vector2f const vec { 0.0f, 1.0f };
    ASSERT_EQ(dot(vec, vec), 1.0f);
}

TEST(Dot, SameVector2)
{
    jt::Vector2f const vec { 1.0f, 0.0f };
    ASSERT_EQ(dot(vec, vec), 1.0f);
}

TEST(Dot, OrthogonalVectors1)
{
    jt::Vector2f const vec1 { 1.0f, 0.0f };
    jt::Vector2f const vec2 { 0.0f, 1.0f };
    ASSERT_EQ(dot(vec1, vec2), 0.0f);
}

TEST(Dot, OrthogonalVectors2)
{
    jt::Vector2f const vec1 { 1.0f, 0.0f };
    jt::Vector2f const vec2 { 0.0f, 1.0f };
    ASSERT_EQ(dot(vec2, vec1), 0.0f);
}

TEST(Dot, OrthogonalVectors3)
{
    jt::Vector2f const vec1 { -1.0f, 0.0f };
    jt::Vector2f const vec2 { 0.0f, 1.0f };
    ASSERT_EQ(dot(vec2, vec1), 0.0f);
}

TEST(Dot, OrthogonalVectors4)
{
    jt::Vector2f const vec1 { 1.0f, 0.0f };
    jt::Vector2f const vec2 { 0.0f, -1.0f };
    ASSERT_EQ(dot(vec2, vec1), 0.0f);
}

TEST(CheckIsIn, Inside)
{
    jt::Rectf const rect { 1.0f, 1.0f, 1.0f, 1.0f };
    jt::Vector2f const point { 1.5f, 1.5f };
    ASSERT_TRUE(jt::MathHelper::checkIsIn(rect, point));
}

TEST(CheckIsIn, OutsideX)
{
    jt::Rectf const rect { 1.0f, 1.0f, 1.0f, 1.0f };
    jt::Vector2f const point { -1.5f, 1.5f };
    ASSERT_FALSE(jt::MathHelper::checkIsIn(rect, point));
}

TEST(CheckIsIn, OutsideY)
{
    jt::Rectf const rect { 1.0f, 1.0f, 1.0f, 1.0f };
    jt::Vector2f const point { 1.5f, 5.5f };
    ASSERT_FALSE(jt::MathHelper::checkIsIn(rect, point));
}

TEST(CastToInteger, CorrectlyCastsDown)
{
    std::vector<std::pair<float, float>> const testData {
        // clang-format off
        std::make_pair(0.0f, 0.0f),
        std::make_pair(100.0f, 100.0f),
        std::make_pair(0.9f, 0.0f),
        std::make_pair(0.1f, 0.0f),
        std::make_pair(-0.1f, -0.0f),
        std::make_pair(1000.1f, 1000.0f),
        // clang-format on
    };

    for (auto const& kvp : testData) {
        auto const castedVector
            = jt::MathHelper::castToInteger(jt::Vector2f { kvp.first, kvp.first });
        auto const expectedResult = jt::Vector2f { kvp.second, kvp.second };
        ASSERT_NEAR(castedVector.x, expectedResult.x, 0.0001f);
        ASSERT_NEAR(castedVector.y, expectedResult.y, 0.0001f);
    }
}
