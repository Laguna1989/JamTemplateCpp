#include "drawable_helpers.hpp"
#include "shape.hpp"
#include "sprite.hpp"
#include "text.hpp"
#include <gtest/gtest.h>

TEST(DrawableHelpersTest, CreateRectShape)
{
    float x = 100.0f;
    float y = 200.0f;
    auto const shape = jt::dh::createRectShape({ x, y }, jt::colors::Green);
    ASSERT_NE(shape, nullptr);
    EXPECT_FLOAT_EQ(shape->getLocalBounds().width(), x);
    EXPECT_FLOAT_EQ(shape->getLocalBounds().height(), y);
    EXPECT_EQ(shape->getColor(), jt::colors::Green);
}

TEST(DrawableHelpersTest, createVignette)
{
    float x = 150.0f;
    float y = 50.0f;
    auto const vignette = jt::dh::createVignette({ x, y });
    ASSERT_NE(vignette, nullptr);
    EXPECT_FLOAT_EQ(vignette->getLocalBounds().width(), x);
    EXPECT_FLOAT_EQ(vignette->getLocalBounds().height(), y);
}

TEST(DrawableHelpersTest, createText)
{
    std::shared_ptr<jt::renderTarget> rt { nullptr };
    auto const text = jt::dh::createText(rt, "assets/font.ttf", 24, jt::colors::Green);
    ASSERT_NE(text, nullptr);
    EXPECT_EQ(text->getColor(), jt::colors::Green);
}
