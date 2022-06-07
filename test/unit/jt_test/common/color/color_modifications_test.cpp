#include <color/color_modifications.hpp>
#include <color/make_color.hpp>
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

TEST(ColorModificationTest, SaturateRed)
{
    auto const initialColor = jt::MakeColor::FromHSV(0.0f, 80.0f, 100.0f);
    auto const saturatedColor = jt::ColorModifications::saturate(initialColor, 20.0f);
    auto const expectedColor = jt::MakeColor::FromHSV(0.0f, 100.0f, 100.0f);

    ASSERT_EQ(saturatedColor, expectedColor);
}

TEST(ColorModificationTest, SaturateGreen)
{
    auto const initialColor = jt::MakeColor::FromHSV(120.0f, 40.0f, 100.0f);
    auto const saturatedColor = jt::ColorModifications::saturate(initialColor, 60.0f);
    auto const expectedColor = jt::MakeColor::FromHSV(120.0f, 100.0f, 100.0f);

    ASSERT_EQ(saturatedColor, expectedColor);
}

TEST(ColorModificationTest, OverSaturateGreen)
{
    auto const initialColor = jt::MakeColor::FromHSV(120.0f, 60.0f, 100.0f);
    auto const saturatedColor = jt::ColorModifications::saturate(initialColor, 60.0f);
    auto const expectedColor = jt::MakeColor::FromHSV(120.0f, 100.0f, 100.0f);

    ASSERT_EQ(saturatedColor, expectedColor);
}

TEST(ColorModificationTest, RotateRedBy360ResultsInSameColor)
{
    auto const initialColor = jt::MakeColor::FromHSV(0.0f, 100.0f, 100.0f);
    auto const rotatedHueColor = jt::ColorModifications::rotateHue(initialColor, 360.0f);

    ASSERT_EQ(rotatedHueColor, initialColor);
}

TEST(ColorModificationTest, RotateGreenBy720ResultsInSameColor)
{
    auto const initialColor = jt::MakeColor::FromHSV(120.0f, 100.0f, 100.0f);
    auto const rotatedHueColor = jt::ColorModifications::rotateHue(initialColor, 720.0f);

    ASSERT_EQ(rotatedHueColor, initialColor);
}

TEST(ColorModificationTest, RotateRedBy120ResultsInGreen)
{
    auto const initialColor = jt::MakeColor::FromHSV(0.0f, 100.0f, 100.0f);
    auto const rotatedHueColor = jt::ColorModifications::rotateHue(initialColor, 120.0f);
    auto const expectedColor = jt::MakeColor::FromHSV(120.0f, 100.0f, 100.0f);

    ASSERT_EQ(rotatedHueColor, expectedColor);
}

TEST(ColorModificationTest, RotateRedBy240ResultsInBlue)
{
    auto const initialColor = jt::MakeColor::FromHSV(0.0f, 100.0f, 100.0f);
    auto const rotatedHueColor = jt::ColorModifications::rotateHue(initialColor, 240.0f);
    auto const expectedColor = jt::MakeColor::FromHSV(240.0f, 100.0f, 100.0f);

    ASSERT_EQ(rotatedHueColor, expectedColor);
}

TEST(ColorModificationTest, DarkenRedResultsInDarkerRed)
{
    auto const initialColor = jt::MakeColor::FromHSV(0.0f, 100.0f, 100.0f);
    auto const darkenedColor = jt::ColorModifications::darken(initialColor, 50.0f);
    auto const expectedColor = jt::MakeColor::FromHSV(0.0f, 100.0f, 50.0f);

    ASSERT_EQ(darkenedColor, expectedColor);
}

TEST(ColorModificationTest, LightenDarkerBlueResultsInBlue)
{
    auto const initialColor = jt::MakeColor::FromHSV(240.0f, 100.0f, 50.0f);
    auto const lightenedColor = jt::ColorModifications::lighten(initialColor, 50.0f);
    // Due to rounding errors in hsv2rgb the resulting color is not "true" blue
    auto const expectedColor = jt::MakeColor::FromRGB(0, 0, 254);

    ASSERT_EQ(lightenedColor, expectedColor);
}
