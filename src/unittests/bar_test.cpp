#include "bar.hpp"
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

TEST(BarTest, SetCurrentValueBelowZero)
{
    jt::Bar b { 5.0f, 10.0f };

    float const max = 100.0f;
    b.setMaxValue(max);

    float const current = -1.5f;
    b.setCurrentValue(current);

    EXPECT_FLOAT_EQ(b.getCurrentValue(), 0.0f);
    EXPECT_FLOAT_EQ(b.getValueFraction(), 0.0f);
}

TEST(BarTest, SetCurrentValueAboveMaxValue)
{
    jt::Bar b { 5.0f, 10.0f };

    float const max = 100.0f;
    b.setMaxValue(max);

    float const current = max + 15.0f;
    b.setCurrentValue(current);

    EXPECT_FLOAT_EQ(b.getCurrentValue(), max);
    EXPECT_FLOAT_EQ(b.getValueFraction(), 1.0f);
}

TEST(BarTest, ColorsCanBeSet)
{
    jt::Bar b { 5.0f, 10.0f };

    b.setFrontColor(jt::colors::Black);
    b.setBackColor(jt::colors::White);

    b.setColor(jt::colors::Green);

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

TEST(BarTest, VerticalBar)
{
    jt::Bar b { 5.0f, 100.0f, false };
    b.update(0.1f);
    b.draw(nullptr);

    SUCCEED();
}

TEST(BarTest, SetFrontColor)
{
    jt::Bar b { 5.0f, 100.0f };
    b.setFrontColor(jt::colors::Red);
    ASSERT_EQ(b.getColor(), jt::colors::Red);
}

TEST(BarTest, SetBackgroundColor)
{
    jt::Bar b { 5.0f, 100.0f };
    b.setBackColor(jt::colors::Yellow);
    SUCCEED();
}

TEST(BarTest, RotateHasNoEffect)
{
    jt::Bar b { 10.0f, 10.0f };
    b.setRotation(22.0f);
    SUCCEED();
}

TEST(BarTest, SetPositionSetsCorrectPosition)
{
    jt::Bar b { 10.0f, 10.0f };
    b.setPosition(jt::Vector2 { 100.0f, 100.0f });
    auto const result = b.getPosition();
    EXPECT_FLOAT_EQ(result.x(), 100.0f);
    EXPECT_FLOAT_EQ(result.y(), 100.0f);
}

TEST(BarTest, ScaleBarSetsScale)
{
    jt::Bar b { 10.0f, 10.0f };
    b.setScale(jt::Vector2 { 100.0f, 100.0f });
    auto const result = b.getScale();
    EXPECT_FLOAT_EQ(result.x(), 100.0f);
    EXPECT_FLOAT_EQ(result.y(), 100.0f);
}

TEST(BarTest, SetOriginSetsOrigin)
{
    jt::Bar b { 10.0f, 10.0f };
    b.setOrigin(jt::Vector2 { 100.0f, 100.0f });
    auto const result = b.getOrigin();
    EXPECT_FLOAT_EQ(result.x(), 100.0f);
    EXPECT_FLOAT_EQ(result.y(), 100.0f);
}
