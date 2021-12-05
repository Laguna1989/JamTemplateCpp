#include "bar.hpp"
#include "sdl_setup.hpp"
#include "texture_manager_impl.hpp"
#include <gtest/gtest.h>
#include <stdexcept>

TEST(BarTest, BarInitialValues)
{
    auto tm = std::make_shared<jt::TextureManagerImpl>();
    tm->setRenderer(getRenderTarget());
    float const x = 64.0f;
    float const y = 16.0f;
    jt::Bar b { x, y, true, tm };
    ASSERT_FLOAT_EQ(b.getLocalBounds().width(), x);
    ASSERT_FLOAT_EQ(b.getLocalBounds().height(), y);
    ASSERT_FLOAT_EQ(b.getMaxValue(), 1.0f);
    ASSERT_FLOAT_EQ(b.getCurrentValue(), 0.0f);
}

TEST(BarTest, SetMaxValueWillCorrectlySetValue)
{
    auto tm = std::make_shared<jt::TextureManagerImpl>();
    tm->setRenderer(getRenderTarget());
    jt::Bar b { 5.0f, 10.0f, true, tm };

    float const expected = 15.0f;
    b.setMaxValue(expected);
    ASSERT_FLOAT_EQ(b.getMaxValue(), expected);
}

TEST(BarTest, SetNegativeMaxValueRaisesException)
{
    auto tm = std::make_shared<jt::TextureManagerImpl>();
    tm->setRenderer(getRenderTarget());
    jt::Bar b { 5.0f, 10.0f, true, tm };
    ASSERT_THROW(b.setMaxValue(-5.0f), std::invalid_argument);
}

class BarCurrentValueTestFixture : public ::testing::TestWithParam<std::pair<float, float>> {
protected:
    float max;
    float current;
    std::shared_ptr<jt::TextureManagerInterface> tm;
    std::shared_ptr<jt::Bar> bar { nullptr };

    void SetUp() override
    {
        tm = std::make_shared<jt::TextureManagerImpl>();
        tm->setRenderer(getRenderTarget());
        bar = std::make_shared<jt::Bar>(5.0f, 10.0f, true, tm);
        max = GetParam().first;
        current = GetParam().second;
        bar->setMaxValue(max);
        bar->setCurrentValue(current);
    }
};

TEST_P(BarCurrentValueTestFixture, GetCurrentValue)
{
    ASSERT_FLOAT_EQ(bar->getCurrentValue(), current);
}

TEST_P(BarCurrentValueTestFixture, GetCurrentValueFraction)
{
    ASSERT_FLOAT_EQ(bar->getValueFraction(), current / max);
}

INSTANTIATE_TEST_SUITE_P(BarCurrentValueTest, BarCurrentValueTestFixture,
    ::testing::Values(
        std::make_pair(100.0f, 50.0f), std::make_pair(65.0f, 65.0f), std::make_pair(1.0f, 0.123f)));

TEST(BarTest, SetCurrentValueBelowZero)
{
    auto tm = std::make_shared<jt::TextureManagerImpl>();
    tm->setRenderer(getRenderTarget());
    jt::Bar b { 5.0f, 10.0f, true, tm };

    float const current = -1.5f;
    b.setCurrentValue(current);

    ASSERT_FLOAT_EQ(b.getCurrentValue(), 0.0f);
    ASSERT_FLOAT_EQ(b.getValueFraction(), 0.0f);
}

TEST(BarTest, SetCurrentValueAboveMaxValue)
{
    auto tm = std::make_shared<jt::TextureManagerImpl>();
    tm->setRenderer(getRenderTarget());
    jt::Bar b { 5.0f, 10.0f, true, tm };

    float const max = 100.0f;
    b.setMaxValue(max);

    float const current = max + 15.0f;
    b.setCurrentValue(current);

    ASSERT_FLOAT_EQ(b.getCurrentValue(), max);
    ASSERT_FLOAT_EQ(b.getValueFraction(), 1.0f);
}

TEST(BarTest, VerticalBar)
{
    auto tm = std::make_shared<jt::TextureManagerImpl>();
    tm->setRenderer(getRenderTarget());
    jt::Bar b { 5.0f, 100.0f, false, tm };
    b.update(0.1f);
    b.draw(nullptr);

    SUCCEED();
}

TEST(BarTest, SetFrontColor)
{
    auto tm = std::make_shared<jt::TextureManagerImpl>();
    tm->setRenderer(getRenderTarget());
    jt::Bar b { 5.0f, 100.0f, true, tm };
    b.setFrontColor(jt::colors::Red);
    ASSERT_EQ(b.getColor(), jt::colors::Red);
}

TEST(BarTest, SetBackgroundColor)
{
    auto tm = std::make_shared<jt::TextureManagerImpl>();
    tm->setRenderer(getRenderTarget());
    jt::Bar b { 5.0f, 100.0f, true, tm };
    b.setBackColor(jt::colors::Yellow);
    ASSERT_EQ(b.getBackColor(), jt::colors::Yellow);
}
