#include "Bar.hpp"
#include <gtest/gtest.h>

TEST(BarTest, BarInitialValues)
{
    float const x = 64.0f;
    float const y = 16.0f;
    jt::Bar b { x, y };
    EXPECT_FLOAT_EQ(b.getLocalBounds().width(), x);
    EXPECT_FLOAT_EQ(b.getLocalBounds().height(), y);
}

TEST(BarTest, PositiveMaxValueDoesNotTriggerAssertion)
{
    jt::Bar b { 5.0f, 10.0f };

    b.setMaxValue(15.0f);
    SUCCEED();
}

TEST(BarTest, NegativeMaxValueTriggersAssertion)
{
    jt::Bar b { 5.0f, 10.0f };

    EXPECT_DEATH(b.setMaxValue(-5.0f), "");
}
