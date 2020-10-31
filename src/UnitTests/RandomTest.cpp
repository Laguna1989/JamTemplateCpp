#include "../JamTemplate/Random.hpp"
#include "gtest/gtest.h"
#include <utility>

using JamTemplate::Random;
using v = sf::Vector2f;

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
