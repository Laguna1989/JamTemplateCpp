#include <ease/back.hpp>
#include <ease/circ.hpp>
#include <ease/cubic.hpp>
#include <ease/quad.hpp>
#include <ease/quart.hpp>
#include <ease/quint.hpp>
#include <cmath>
#include <functional>
#include <gtest/gtest.h>
#include <string>

namespace {

using EaseFunction = std::function<float(float, float, float, float)>;
using NormalizedEase = std::function<float(float)>;

// Reference curves
float power(float const p, int exponent) { return std::pow(p, static_cast<float>(exponent)); }

NormalizedEase powerIn(int exponent)
{
    return [exponent](float const p) { return power(p, exponent); };
}

NormalizedEase powerOut(int exponent)
{
    return [exponent](float const p) { return 1.0f - power(1.0f - p, exponent); };
}

NormalizedEase powerInOut(int exponent)
{
    return [exponent](float const p) {
        if (p < 0.5f) {
            return power(2.0f * p, exponent) / 2.0f;
        }
        return 1.0f - power(2.0f - 2.0f * p, exponent) / 2.0f;
    };
}

float circIn(float const p) { return 1.0f - std::sqrt(1.0f - p * p); }

float circOut(float const p) { return std::sqrt(1.0f - (p - 1.0f) * (p - 1.0f)); }

float circInOut(float const p)
{
    if (p < 0.5f) {
        return circIn(2.0f * p) / 2.0f;
    }
    return 0.5f + circOut(2.0f * p - 1.0f) / 2.0f;
}

constexpr float backOvershoot { 1.70158f };
constexpr float backOvershootInOut { backOvershoot * 1.525f };

float backIn(float const p) { return p * p * ((backOvershoot + 1.0f) * p - backOvershoot); }

float backOut(float const p)
{
    float const q { p - 1.0f };
    return q * q * ((backOvershoot + 1.0f) * q + backOvershoot) + 1.0f;
}

float backInOut(float const p)
{
    float const q { 2.0f * p };
    if (q < 1.0f) {
        return q * q * ((backOvershootInOut + 1.0f) * q - backOvershootInOut) / 2.0f;
    }
    float const r { q - 2.0f };
    return (r * r * ((backOvershootInOut + 1.0f) * r + backOvershootInOut) + 2.0f) / 2.0f;
}

struct EaseTestCase {
    std::string name;
    EaseFunction function;
    NormalizedEase reference;
};

void PrintTo(EaseTestCase const& testCase, std::ostream* os) { *os << testCase.name; }

class PennerEaseTestFixture : public ::testing::TestWithParam<EaseTestCase> { };

constexpr float startValue { 2.0f };
constexpr float changeValue { 3.0f };
constexpr float duration { 4.0f };
constexpr float tolerance { 1e-5f };

} // namespace

TEST_P(PennerEaseTestFixture, StartsAtStartValue)
{
    auto const& testCase = GetParam();
    EXPECT_NEAR(testCase.function(0.0f, startValue, changeValue, duration), startValue, tolerance);
}

TEST_P(PennerEaseTestFixture, EndsAtStartPlusChange)
{
    auto const& testCase = GetParam();
    EXPECT_NEAR(testCase.function(duration, startValue, changeValue, duration),
        startValue + changeValue, tolerance);
}

TEST_P(PennerEaseTestFixture, MatchesReferenceCurve)
{
    auto const& testCase = GetParam();
    constexpr int steps { 32 };
    for (int i = 0; i <= steps; ++i) {
        float const t { duration * static_cast<float>(i) / static_cast<float>(steps) };
        float const expected { startValue + changeValue * testCase.reference(t / duration) };
        EXPECT_NEAR(testCase.function(t, startValue, changeValue, duration), expected, tolerance)
            << "at t = " << t;
    }
}

INSTANTIATE_TEST_SUITE_P(PennerEaseTest, PennerEaseTestFixture,
    ::testing::Values(EaseTestCase { "quadIn", jt::ease::quad::easeIn, powerIn(2) },
        EaseTestCase { "quadOut", jt::ease::quad::easeOut, powerOut(2) },
        EaseTestCase { "quadInOut", jt::ease::quad::easeInOut, powerInOut(2) },
        EaseTestCase { "cubicIn", jt::ease::cubic::easeIn, powerIn(3) },
        EaseTestCase { "cubicOut", jt::ease::cubic::easeOut, powerOut(3) },
        EaseTestCase { "cubicInOut", jt::ease::cubic::easeInOut, powerInOut(3) },
        EaseTestCase { "quartIn", jt::ease::quart::easeIn, powerIn(4) },
        EaseTestCase { "quartOut", jt::ease::quart::easeOut, powerOut(4) },
        EaseTestCase { "quartInOut", jt::ease::quart::easeInOut, powerInOut(4) },
        EaseTestCase { "quintIn", jt::ease::quint::easeIn, powerIn(5) },
        EaseTestCase { "quintOut", jt::ease::quint::easeOut, powerOut(5) },
        EaseTestCase { "quintInOut", jt::ease::quint::easeInOut, powerInOut(5) },
        EaseTestCase { "circIn", jt::ease::circ::easeIn, circIn },
        EaseTestCase { "circOut", jt::ease::circ::easeOut, circOut },
        EaseTestCase { "circInOut", jt::ease::circ::easeInOut, circInOut },
        EaseTestCase { "backIn", jt::ease::back::easeIn, backIn },
        EaseTestCase { "backOut", jt::ease::back::easeOut, backOut },
        EaseTestCase { "backInOut", jt::ease::back::easeInOut, backInOut }),
    [](auto const& info) { return info.param.name; });
