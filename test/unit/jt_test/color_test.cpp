#include "color/color.hpp"
#include <gtest/gtest.h>
#include <type_traits>

TEST(ColorTest, IsDefaultConstructible)
{
    ASSERT_TRUE(std::is_default_constructible<jt::Color>::value);
}

TEST(ColorTest, InitialValues)
{
    jt::Color const color {};
    ASSERT_EQ(color, jt::colors::Black);
}

TEST(ColorTest, SetValues)
{
    jt::Color const color { 0, 111, 222 };
    ASSERT_EQ(color.r, 0);
    ASSERT_EQ(color.g, 111);
    ASSERT_EQ(color.b, 222);
}

/*
TEST(ColorTest, DesaturateRed)
{
    auto const initialColor = jt::MakeColor::FromHSV(0, 100.0f, 100.0f);
    auto const desaturatedColor = initialColor.desatrate(20.0f);
    auto const expectedColor = jt::MakeColor::FromHSV(0, 80.0f, 100.0f);

    ASSERT_EQ(desaturatedColor, expectedColor);
}*/
