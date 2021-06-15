#include "Conversions.hpp"
#include "Vector.hpp"
#include "gtest/gtest.h"
#include <limits>
#include <utility>

using namespace jt::Conversion;

using tt = std::pair<float, float>;

class ConversionsTestFixture : public ::testing::TestWithParam<tt> {
};

using nl = std::numeric_limits<float>;

INSTANTIATE_TEST_SUITE_P(ConversionsTest, ConversionsTestFixture,
    ::testing::Values(std::make_pair(1.0f, 5.0f), std::make_pair(-2.5f, -3.3333f),
        std::make_pair(nl::min(), nl::max()), std::make_pair(nl::epsilon(), nl::infinity())));

TEST_P(ConversionsTestFixture, box2dVectorToSFMLVector)
{
    ::jt::Vector2 const expected { GetParam().first, GetParam().second };
    b2Vec2 const input { GetParam().first, GetParam().second };
    EXPECT_TRUE(vec(input) == expected);
}

TEST_P(ConversionsTestFixture, SFMLVectorToB2Vec)
{
    b2Vec2 const expected { GetParam().first, GetParam().second };
    jt::Vector2 const input { GetParam().first, GetParam().second };
    EXPECT_TRUE(vec(input) == expected);
}

TEST_P(ConversionsTestFixture, TsonVecfToSFMLVector)
{
    ::jt::Vector2 const expected { GetParam().first, GetParam().second };
    tson::Vector2f const input { GetParam().first, GetParam().second };
    EXPECT_TRUE(vec(input) == expected);
}

TEST_P(ConversionsTestFixture, TsonVeciToSFMLVector)
{
    ::jt::Vector2 const expected { static_cast<float>(static_cast<int>(GetParam().first)),
        static_cast<float>(static_cast<int>(GetParam().second)) };
    tson::Vector2i const input { static_cast<int>(GetParam().first),
        static_cast<int>(GetParam().second) };
    EXPECT_TRUE(vec(input) == expected);
}
