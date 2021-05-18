#include "Bar.hpp"
#include <gtest/gtest.h>

TEST(BarTest, BarInitialValues)
{
    float const x = 64.0f;
    float const y = 16.0f;
    jt::Bar b { x, y };
    EXPECT_FLOAT_EQ(b.getLocalBounds().width(), x);
    EXPECT_FLOAT_EQ(b.getLocalBounds().height(), y);
    EXPECT_FLOAT_EQ(b.getMaxValue(), 1.0f);
    EXPECT_FLOAT_EQ(b.getCurrentValue(), 0.0f);
}

TEST(BarTest, PositiveMaxValueDoesNotTriggerAssertion)
{
    jt::Bar b { 5.0f, 10.0f };

    float const expected = 15.0f;
    b.setMaxValue(expected);
    EXPECT_FLOAT_EQ(b.getMaxValue(), expected);
}

TEST(BarTest, NegativeMaxValueTriggersAssertion)
{
    jt::Bar b { 5.0f, 10.0f };
    EXPECT_DEATH(b.setMaxValue(-5.0f), "");
}

TEST(BarTest, SetCurrentValueSetsCorrectValue)
{
    jt::Bar b { 5.0f, 10.0f };

    float const max = 100.0f;
    b.setMaxValue(max);

    float const current = 50.0f;
    b.setCurrentValue(current);

    EXPECT_FLOAT_EQ(b.getCurrentValue(), current);
    EXPECT_FLOAT_EQ(b.getValueFraction(), current / max);
}

TEST(BarTest, ColorsCanBeSet)
{
    jt::Bar b { 5.0f, 10.0f };

    b.setFrontColor(jt::colors::Black);
    b.setBackColor(jt::colors::White);

    b.setFrontColor(jt::colors::Red);
    b.setBackColor(jt::colors::Blue);

    SUCCEED();
}

TEST(BarTest, CanBeDrawnWithNullptrRenderTarget)
{
    jt::Bar b { 5.0f, 10.0f };

    b.update(0.1f);
    b.draw(nullptr);

    SUCCEED();
}
