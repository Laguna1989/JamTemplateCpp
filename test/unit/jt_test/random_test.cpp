#include "color_helpers.hpp"
#include "random/random.hpp"
#include "random/random_sample_and_hold.hpp"
#include "vector.hpp"
#include "gtest/gtest.h"
#include <utility>

using jt::Random;
using v = jt::Vector2f;

class RandomIntTestFixture : public ::testing::TestWithParam<std::pair<int, int>> {
};

INSTANTIATE_TEST_SUITE_P(RandomIntTest, RandomIntTestFixture,
    ::testing::Values(std::make_pair(1, 6), std::make_pair(0, 100), std::make_pair(-20, 20),
        std::make_pair(3300, 3400), std::make_pair(0, 1)));

TEST_P(RandomIntTestFixture, RandomInt)
{
    int const lower { GetParam().first };
    int const upper { GetParam().second };
    for (auto i = 0U; i != 1000; ++i) {
        int const v { Random::getInt(lower, upper) };
        EXPECT_GE(v, lower);
        EXPECT_LE(v, upper);
    }
}

class RandomFloatTestFixture : public ::testing::TestWithParam<std::pair<float, float>> {
};

INSTANTIATE_TEST_SUITE_P(RandomFloatTest, RandomFloatTestFixture,
    ::testing::Values(
        std::make_pair(0.0f, 1.0f), std::make_pair(-20.0f, 20.0f), std::make_pair(0.0f, 100.0f)));

TEST_P(RandomFloatTestFixture, RandomFloat)
{
    float const lower { GetParam().first };
    float const upper { GetParam().second };
    for (auto i = 0U; i != 1000; ++i) {
        float const v { Random::getFloat(lower, upper) };
        EXPECT_GE(v, lower);
        EXPECT_LE(v, upper);
    }
}

TEST(RandomChanceTest, ChanceZeroAlwaysFalse)
{
    for (auto i = 0U; i != 1000; ++i) {
        EXPECT_FALSE(Random::getChance(0.0f));
    }
}
TEST(RandomChanceTest, ChanceZeroAlwaysTrue)
{
    for (auto i = 0U; i != 1000; ++i) {
        EXPECT_TRUE(Random::getChance(1.0f));
    }
}

class RandomFloatGaussTestFixture : public ::testing::TestWithParam<std::pair<float, float>> {
};

INSTANTIATE_TEST_SUITE_P(RandomFloatGaussTest, RandomFloatGaussTestFixture,
    ::testing::Values(std::make_pair(0.0f, 1.0f), std::make_pair(0.0f, 500.0f),
        std::make_pair(0.0f, 0.1f),
        std::make_pair(
            std::numeric_limits<float>::epsilon(), std::numeric_limits<float>::epsilon())));

TEST_P(RandomFloatGaussTestFixture, RandomFloat)
{
    float const mu { GetParam().first };
    float const sigma { GetParam().second };
    for (auto i = 0U; i != 1000; ++i) {
        auto const r = Random::getFloatGauss(mu, sigma);
        EXPECT_GT(r, std::numeric_limits<float>::lowest());
        EXPECT_LT(r, std::numeric_limits<float>::max());
    }
}

#ifndef JT_ENABLE_WEB
TEST(RandomGaussTestException, ZeroSigma)
{
    EXPECT_THROW(Random::getFloatGauss(0.0f, 0), std::invalid_argument);
}

TEST(RandomGaussTestException, NegativeSigma)
{
    EXPECT_THROW(Random::getFloatGauss(0.0f, -2.0f), std::invalid_argument);
}
#endif

TEST(RandomColor, NoThrow) { EXPECT_NO_THROW(Random::getRandomColor()); }

TEST(RandomColor, NotEqual)
{
    auto const c1 = Random::getRandomColor();
    auto const c2 = Random::getRandomColor();
    EXPECT_TRUE(c1 != c2);
}

TEST(RandomColor, HSV)
{
    auto col = Random::getRandomColorHSV(0.0f, 0.0f, 90.0f, 100.0f, 0.0f, 100.0f);

    auto [h, s, v] = jt::ColorHelpers::rgb2hsv(col.r, col.g, col.b);
    ASSERT_FLOAT_EQ(h, 0.0f);
}

TEST(RandomInRect, Valid)
{
    auto const lower = 0.0f;
    auto const upper = 10.0f;
    for (auto i = 0U; i != 1000; ++i) {
        auto const v = Random::getRandomPointIn(jt::Rectf { lower, lower, upper, upper });
        EXPECT_GT(v.x, lower);
        EXPECT_GT(v.y, lower);
        EXPECT_LT(v.x, upper);
        EXPECT_LT(v.y, upper);
    }
}

class RandomSetSeedTestFixture : public ::testing::TestWithParam<unsigned int> {
};

INSTANTIATE_TEST_SUITE_P(RandomSetSeedTest, RandomSetSeedTestFixture,
    ::testing::Values(0U, 1U, 10U, 100U, 1000U, std::numeric_limits<unsigned int>::epsilon(),
        std::numeric_limits<unsigned int>::min(), std::numeric_limits<unsigned int>::max()));

TEST_P(RandomSetSeedTestFixture, Values) { EXPECT_NO_THROW(Random::setSeed(GetParam())); }

TEST(RandomSetTimeAsSeed, NoThrow) { EXPECT_NO_THROW(Random::useTimeAsRandomSeed()); }

TEST(SampleAndHold, ReturnsSameSampleWithoutUpdate)
{
    jt::SampleAndHold sah { 10000.0f, 0.000001f };
    auto const initial = sah.getFloat();

    auto const nextValue = sah.getFloat();
    EXPECT_FLOAT_EQ(initial, nextValue);
}

TEST(SampleAndHold, ReturnsSameSampleAfterUpdateShortThanTimerMu)
{
    jt::SampleAndHold sah { 10000.0f, 0.000001f };
    auto const initial = sah.getFloat();

    sah.update(0.1f);
    auto const nextValue = sah.getFloat();
    EXPECT_FLOAT_EQ(initial, nextValue);
}

TEST(SampleAndHold, ReturnsDifferentSampleAfterUpdateLongerThanTimerMu)
{
    jt::SampleAndHold sah { 100.0f, 0.000001f };
    auto const initial = sah.getFloat();

    sah.update(200.0f);
    auto const nextValue = sah.getFloat();
    EXPECT_NE(initial, nextValue);
}
