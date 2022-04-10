#include "color/color_modifications.hpp"
#include "color/make_color.hpp"
#include <gtest/gtest.h>

TEST(ColorModificationTest, DesaturateRed)
{
    auto const initialColor = jt::MakeColor::FromHSV(0, 100.0f, 100.0f);
    auto const desaturatedColor = jt::ColorModifications::desaturate(initialColor, 20.0f);
    auto const expectedColor = jt::MakeColor::FromHSV(0, 80.0f, 100.0f);

    ASSERT_EQ(desaturatedColor, expectedColor);
}

TEST(ColorModificationTest, DesaturateGreen)
{
    auto const initialColor = jt::MakeColor::FromHSV(120.0f, 100.0f, 100.0f);
    auto const desaturatedColor = jt::ColorModifications::desaturate(initialColor, 60.0f);
    auto const expectedColor = jt::MakeColor::FromHSV(120.0f, 40.0f, 100.0f);

    ASSERT_EQ(desaturatedColor, expectedColor);
}

TEST(ColorModificationTest, OverDesaturateGreen)
{
    auto const initialColor = jt::MakeColor::FromHSV(120.0f, 40.0f, 100.0f);
    auto const desaturatedColor = jt::ColorModifications::desaturate(initialColor, 60.0f);
    auto const expectedColor = jt::MakeColor::FromHSV(120.0f, 0.0f, 100.0f);

    ASSERT_EQ(desaturatedColor, expectedColor);
}
