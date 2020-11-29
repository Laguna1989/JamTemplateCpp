﻿#include "Random.hpp"
#include "vector.hpp"
#include "gtest/gtest.h"
#include <utility>

using jt::Random;
using v = jt::vector2;

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
    ::testing::Values(std::make_pair(0.0f, 1.0f), std::make_pair(0.0f, 500),
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

TEST(RandomGaussTestException, ZeroSigma)
{
    EXPECT_THROW(Random::getFloatGauss(0.0f, 0), std::invalid_argument);
}

TEST(RandomGaussTestException, NegativeSigma)
{
    EXPECT_THROW(Random::getFloatGauss(0.0f, -2.0f), std::invalid_argument);
}

TEST(RandomColor, NoThrow) { EXPECT_NO_THROW(Random::getRandomColor()); }

TEST(RandomInRect, Valid)
{
    auto const lower = 0.0f;
    auto const upper = 10.0f;
    for (auto i = 0U; i != 1000; ++i) {
        auto const v = Random::getRandomPointin(jt::rect { lower, lower, upper, upper });
        EXPECT_GT(v.x(), lower);
        EXPECT_GT(v.y(), lower);
        EXPECT_LT(v.x(), upper);
        EXPECT_LT(v.y(), upper);
    }
}

class RandomSetSeedTestFixture : public ::testing::TestWithParam<unsigned int> {
};

INSTANTIATE_TEST_SUITE_P(RandomSetSeedTest, RandomSetSeedTestFixture,
    ::testing::Values(0U, 1U, 10U, 100U, 1000U, std::numeric_limits<unsigned int>::epsilon(),
        std::numeric_limits<unsigned int>::min(), std::numeric_limits<unsigned int>::max()));

TEST_P(RandomSetSeedTestFixture, Values) { EXPECT_NO_THROW(Random::setSeed(GetParam())); }

TEST(RandomSetTimeAsSeed, NoThrow) { EXPECT_NO_THROW(Random::useTimeAsRandomSeed()); }
