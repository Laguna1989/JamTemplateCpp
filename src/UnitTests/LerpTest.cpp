#include "Lerp.hpp"
#include "gtest/gtest.h"
#include <utility>

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
