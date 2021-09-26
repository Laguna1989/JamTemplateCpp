#include "lerp.hpp"
#include "gtest/gtest.h"
#include <functional>
#include <tuple>

using namespace jt::Lerp;

TEST(LerpTest, LinearZeroToOne)
{
    EXPECT_EQ(linear(0.0f, 1.0f, -0.5f), 0.0f);
    EXPECT_EQ(linear(0.0f, 1.0f, 0.0f), 0.0f);
    EXPECT_EQ(linear(0.0f, 1.0f, 0.5f), 0.5f);
    EXPECT_EQ(linear(0.0f, 1.0f, 1.0f), 1.0f);
    EXPECT_EQ(linear(0.0f, 1.0f, 1.5f), 1.0f);
}

TEST(LerpTest, LinearOneToFive)
{
    EXPECT_EQ(linear(1.0f, 5.0f, -0.5f), 1.0f);
    EXPECT_EQ(linear(1.0f, 5.0f, 0.0f), 1.0f);
    EXPECT_EQ(linear(1.0f, 5.0f, 0.5f), 3.0f);
    EXPECT_EQ(linear(1.0f, 5.0f, 1.0f), 5.0f);
    EXPECT_EQ(linear(1.0f, 5.0f, 1.5f), 5.0f);
}

class LerpTestF : public ::testing::Test {
protected:
    float const input { 0.0f };
    float const expected { 0.0f };
};

TEST_F(LerpTestF, cosine)
{
    auto f = jt::Lerp::cosine<float>;
    ASSERT_EQ(expected, f(input, 0.0f, 1.0f));
}

TEST_F(LerpTestF, bounce)
{
    auto f = jt::Lerp::bounce<float>;
    ASSERT_EQ(expected, f(input, 0.0f, 1.0f));
}

TEST_F(LerpTestF, bounceinvers)
{
    auto f = jt::Lerp::bounceInvers<float>;
    ASSERT_EQ(expected, f(input, 0.0f, 1.0f));
}

TEST_F(LerpTestF, cubic)
{
    auto f = jt::Lerp::cubic<float>;
    ASSERT_EQ(expected, f(input, 0.0f, 1.0f));
}

TEST_F(LerpTestF, cubicinvers)
{
    auto f = jt::Lerp::cubicInvers<float>;
    ASSERT_EQ(expected, f(input, 0.0f, 1.0f));
}
