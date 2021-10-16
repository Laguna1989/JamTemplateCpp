#include "drawable_helpers.hpp"
#include "shape.hpp"
#include "sprite.hpp"
#include "text.hpp"
#include <gtest/gtest.h>

TEST(CreateRectShapeTest, NoNullptr)
{
    auto const shape = jt::dh::createRectShape({ 1.0f, 2.0f }, jt::colors::Green);
    ASSERT_NE(shape, nullptr);
}

TEST(RectCreateRectShapeTest, Size)
{
    jt::Rect expected { 0.0f, 0.0f, 100.0f, 200.0f };
    auto const shape
        = jt::dh::createRectShape({ expected.width(), expected.height() }, jt::colors::Green);

    ASSERT_EQ(shape->getLocalBounds(), expected);
}

TEST(CreateRectShapeTest, Color)
{
    auto const col = jt::colors::Green;
    auto const shape = jt::dh::createRectShape({ 3.0f, 4.0f }, col);
    ASSERT_EQ(shape->getColor(), col);
}

TEST(CreateVignetteTest, NoNullptr)
{
    float const x = 150.0f;
    float const y = 50.0f;
    auto const vignette = jt::dh::createVignette({ x, y });
    ASSERT_NE(vignette, nullptr);
}

TEST(CreateVignetteTest, Size)
{
    float const x = 150.0f;
    float const y = 50.0f;
    auto const vignette = jt::dh::createVignette({ x, y });
    ASSERT_FLOAT_EQ(vignette->getLocalBounds().width(), x);
    ASSERT_FLOAT_EQ(vignette->getLocalBounds().height(), y);
}

TEST(CreateVignetteTest, Color)
{
    float const x = 150.0f;
    float const y = 50.0f;
    auto const vignette = jt::dh::createVignette({ x, y });
    ASSERT_EQ(vignette->getColor(), jt::colors::White);
}

TEST(CreateTextTest, NoNullptr)
{
    std::shared_ptr<jt::renderTarget> rt { nullptr };
    auto const text = jt::dh::createText(rt, "assets/font.ttf", 24, jt::colors::Green);
    ASSERT_NE(text, nullptr);
}

TEST(CreateTextTest, Color)
{
    std::shared_ptr<jt::renderTarget> rt { nullptr };
    auto const text = jt::dh::createText(rt, "assets/font.ttf", 24, jt::colors::Green);
    ASSERT_EQ(text->getColor(), jt::colors::Green);
}
