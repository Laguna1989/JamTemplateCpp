#include <color/color.hpp>
#include <color/color_factory.hpp>
#include <color/color_modifications.hpp>
#include <gtest/gtest.h>

TEST(ColorModificationTest, DesaturateRed)
{
    auto const initialColor = jt::ColorFactory::fromHSV(0, 100.0f, 100.0f);
    auto const desaturatedColor = jt::ColorModifications::desaturate(initialColor, 20.0f);
    auto const expectedColor = jt::ColorFactory::fromHSV(0, 80.0f, 100.0f);

    ASSERT_EQ(desaturatedColor, expectedColor);
}

TEST(ColorModificationTest, DesaturateGreen)
{
    auto const initialColor = jt::ColorFactory::fromHSV(120.0f, 100.0f, 100.0f);
    auto const desaturatedColor = jt::ColorModifications::desaturate(initialColor, 60.0f);
    auto const expectedColor = jt::ColorFactory::fromHSV(120.0f, 40.0f, 100.0f);

    ASSERT_EQ(desaturatedColor, expectedColor);
}

TEST(ColorModificationTest, OverDesaturateGreen)
{
    auto const initialColor = jt::ColorFactory::fromHSV(120.0f, 40.0f, 100.0f);
    auto const desaturatedColor = jt::ColorModifications::desaturate(initialColor, 60.0f);
    auto const expectedColor = jt::ColorFactory::fromHSV(120.0f, 0.0f, 100.0f);

    ASSERT_EQ(desaturatedColor, expectedColor);
}

TEST(ColorModificationTest, SaturateRed)
{
    auto const initialColor = jt::ColorFactory::fromHSV(0.0f, 80.0f, 100.0f);
    auto const saturatedColor = jt::ColorModifications::saturate(initialColor, 20.0f);
    auto const expectedColor = jt::ColorFactory::fromHSV(0.0f, 100.0f, 100.0f);

    ASSERT_EQ(saturatedColor, expectedColor);
}

TEST(ColorModificationTest, SaturateGreen)
{
    auto const initialColor = jt::ColorFactory::fromHSV(120.0f, 40.0f, 100.0f);
    auto const saturatedColor = jt::ColorModifications::saturate(initialColor, 60.0f);
    auto const expectedColor = jt::ColorFactory::fromHSV(120.0f, 100.0f, 100.0f);

    ASSERT_EQ(saturatedColor, expectedColor);
}

TEST(ColorModificationTest, OverSaturateGreen)
{
    auto const initialColor = jt::ColorFactory::fromHSV(120.0f, 60.0f, 100.0f);
    auto const saturatedColor = jt::ColorModifications::saturate(initialColor, 60.0f);
    auto const expectedColor = jt::ColorFactory::fromHSV(120.0f, 100.0f, 100.0f);

    ASSERT_EQ(saturatedColor, expectedColor);
}

TEST(ColorModificationTest, RotateRedBy360ResultsInSameColor)
{
    auto const initialColor = jt::ColorFactory::fromHSV(0.0f, 100.0f, 100.0f);
    auto const rotatedHueColor = jt::ColorModifications::rotateHue(initialColor, 360.0f);

    ASSERT_EQ(rotatedHueColor, initialColor);
}

TEST(ColorModificationTest, RotateGreenBy720ResultsInSameColor)
{
    auto const initialColor = jt::ColorFactory::fromHSV(120.0f, 100.0f, 100.0f);
    auto const rotatedHueColor = jt::ColorModifications::rotateHue(initialColor, 720.0f);

    ASSERT_EQ(rotatedHueColor, initialColor);
}

TEST(ColorModificationTest, RotateRedBy120ResultsInGreen)
{
    auto const initialColor = jt::ColorFactory::fromHSV(0.0f, 100.0f, 100.0f);
    auto const rotatedHueColor = jt::ColorModifications::rotateHue(initialColor, 120.0f);
    auto const expectedColor = jt::ColorFactory::fromHSV(120.0f, 100.0f, 100.0f);

    ASSERT_EQ(rotatedHueColor, expectedColor);
}

TEST(ColorModificationTest, RotateRedBy240ResultsInBlue)
{
    auto const initialColor = jt::ColorFactory::fromHSV(0.0f, 100.0f, 100.0f);
    auto const rotatedHueColor = jt::ColorModifications::rotateHue(initialColor, 240.0f);
    auto const expectedColor = jt::ColorFactory::fromHSV(240.0f, 100.0f, 100.0f);

    ASSERT_EQ(rotatedHueColor, expectedColor);
}

TEST(ColorModificationTest, DarkenRedResultsInDarkerRed)
{
    auto const initialColor = jt::ColorFactory::fromHSV(0.0f, 100.0f, 100.0f);
    auto const darkenedColor = jt::ColorModifications::darken(initialColor, 50.0f);
    auto const expectedColor = jt::ColorFactory::fromHSV(0.0f, 100.0f, 50.0f);

    ASSERT_EQ(darkenedColor, expectedColor);
}

TEST(ColorModificationTest, LightenADarkBlueResultsInBlue)
{
    auto const initialColor = jt::ColorFactory::fromHSV(240.0f, 100.0f, 50.0f);
    auto const lightenedColor = jt::ColorModifications::lighten(initialColor, 50.0f);
    // Due to floating point rounding errors in hsv2rgb the resulting color is not "true" blue
    auto const expectedColor = jt::ColorFactory::fromRGB(0, 0, 254);

    ASSERT_EQ(lightenedColor, expectedColor);
}

TEST(ColorModificationTest, Complement)
{
    std::vector<std::pair<jt::Color, jt::Color>> testData {
        std::make_pair(jt::colors::White, jt::colors::Black),
        std::make_pair(jt::colors::Red, jt::colors::Cyan),
        std::make_pair(jt::colors::Green, jt::colors::Magenta),
        std::make_pair(jt::colors::Blue, jt::colors::Yellow),
    };

    for (auto const& kvp : testData) {
        auto const initialColor = kvp.first;
        auto const expectedColor = kvp.second;
        auto const calculatedComplement = jt::ColorModifications::complement(initialColor);

        ASSERT_EQ(calculatedComplement, expectedColor);
    }
}
