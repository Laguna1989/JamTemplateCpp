#include "conversions.hpp"
#include "vector.hpp"
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

TEST_P(ConversionsTestFixture, box2dVectorToJTVector)
{
    ::jt::Vector2f const expected { GetParam().first, GetParam().second };
    b2Vec2 const input { GetParam().first, GetParam().second };
    ASSERT_EQ(vec(input), expected);
}

TEST_P(ConversionsTestFixture, JTVectorToB2Vec)
{
    b2Vec2 const expected { GetParam().first, GetParam().second };
    jt::Vector2f const input { GetParam().first, GetParam().second };
    ASSERT_EQ(vec(input), expected);
}

TEST_P(ConversionsTestFixture, TsonVecfToJTVector)
{
    ::jt::Vector2f const expected { GetParam().first, GetParam().second };
    tson::Vector2f const input { GetParam().first, GetParam().second };
    ASSERT_EQ(vec(input), expected);
}

TEST_P(ConversionsTestFixture, TsonVeciToJTVector)
{
    ::jt::Vector2f const expected { static_cast<float>(static_cast<int>(GetParam().first)),
        static_cast<float>(static_cast<int>(GetParam().second)) };
    tson::Vector2i const input { static_cast<int>(GetParam().first),
        static_cast<int>(GetParam().second) };
    ASSERT_EQ(vec(input), expected);
}
