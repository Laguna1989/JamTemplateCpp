#include "../JamTemplate/Conversions.hpp"
#include "gtest/gtest.h"
#include <limits>
#include <utility>

using namespace JamTemplate::C;

using tt = std::pair<float, float>;

class ConversionsTestFixture : public ::testing::TestWithParam<tt> {
};

using nl = std::numeric_limits<float>;

INSTANTIATE_TEST_SUITE_P(ConversionsTest, ConversionsTestFixture,
    ::testing::Values(std::make_pair(1.0f, 5.0f), std::make_pair(-2.5f, -3.3333f),
        std::make_pair(nl::min(), nl::max()), std::make_pair(nl::epsilon(), nl::infinity())));

TEST_P(ConversionsTestFixture, box2dVectorToSFMLVector)
{
    ::sf::Vector2f const expected { GetParam().first, GetParam().second };
    b2Vec2 const input { GetParam().first, GetParam().second };
    EXPECT_EQ(vec(input), expected);
}

TEST_P(ConversionsTestFixture, SFMLVectorToB2Vec)
{
    b2Vec2 const expected { GetParam().first, GetParam().second };
    ::sf::Vector2f const input { GetParam().first, GetParam().second };
    EXPECT_EQ(vec(input), expected);
}
