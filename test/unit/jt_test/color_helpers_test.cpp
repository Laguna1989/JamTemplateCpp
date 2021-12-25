#include "color_helpers.hpp"
#include <cmath>
#include <gtest/gtest.h>
#include <tuple>

class ColorHelpersHsv2RgbTestFixture
    : public ::testing::TestWithParam<
          std::tuple<float, float, float, std::uint8_t, std::uint8_t, std::uint8_t>> {
};

TEST_P(ColorHelpersHsv2RgbTestFixture, hsv2rgb)
{
    auto h = std::get<0>(GetParam());
    auto s = std::get<1>(GetParam());
    auto v = std::get<2>(GetParam());
    auto r_expected = std::get<3>(GetParam());
    auto g_expected = std::get<4>(GetParam());
    auto b_expected = std::get<5>(GetParam());

    auto [r, g, b] = jt::ColorHelpers::hsv2rgb(h, s, v);
    ASSERT_EQ(static_cast<int>(r), static_cast<int>(r_expected));
    ASSERT_EQ(static_cast<int>(g), static_cast<int>(g_expected));
    ASSERT_EQ(static_cast<int>(b), static_cast<int>(b_expected));
}

TEST_P(ColorHelpersHsv2RgbTestFixture, rgb2hsv)
{
    auto h_expected = std::get<0>(GetParam());
    auto s_expected = std::get<1>(GetParam());
    auto v_expected = std::get<2>(GetParam());
    auto r = std::get<3>(GetParam());
    auto g = std::get<4>(GetParam());
    auto b = std::get<5>(GetParam());

    if (r == 0 && g == 0 && b == 0) {
        h_expected = 0.0f;
        s_expected = 0.0f;
        v_expected = 0.0f;
    }
    if (h_expected >= 360) {
        h_expected = 0;
    }

    auto [h, s, v] = jt::ColorHelpers::rgb2hsv(r, g, b);
    ASSERT_EQ(round(h), h_expected);
    ASSERT_EQ(round(s), s_expected);
    ASSERT_EQ(round(v), v_expected);
}

INSTANTIATE_TEST_SUITE_P(ColorHelpersHsv2RgbTestNoSaturationNoValue, ColorHelpersHsv2RgbTestFixture,
    ::testing::Values(std::make_tuple(0.0f, 0.0f, 0.0f, 0, 0, 0),
        std::make_tuple(120.0f, 0.0f, 0.0f, 0, 0, 0),
        std::make_tuple(120.0f + 360.0f, 0.0f, 0.0f, 0, 0, 0),
        std::make_tuple(240.0f, 0.0f, 0.0f, 0, 0, 0),
        std::make_tuple(361.0f, 100.0f, 100.0f, 255, 0, 0)));

INSTANTIATE_TEST_SUITE_P(ColorHelpersHsv2RgbTestBasicColors, ColorHelpersHsv2RgbTestFixture,
    ::testing::Values(std::make_tuple(0.0f, 100.0f, 100.0f, 255, 0, 0),
        std::make_tuple(120.0f, 100.0f, 100.0f, 0, 255, 0),
        std::make_tuple(240.0f, 100.0f, 100.0f, 0, 0, 255)));

INSTANTIATE_TEST_SUITE_P(ColorHelpersHsv2RgbTestBasicColorsTwo, ColorHelpersHsv2RgbTestFixture,
    ::testing::Values(std::make_tuple(60.0f, 100.0f, 100.0f, 255, 255, 0),
        std::make_tuple(180.0f, 100.0f, 100.0f, 0, 255, 255),
        std::make_tuple(300.0f, 100.0f, 100.0f, 255, 0, 255)));

INSTANTIATE_TEST_SUITE_P(ColorHelpersHsv2RgbTestComplexColors, ColorHelpersHsv2RgbTestFixture,
    ::testing::Values(std::make_tuple(200.0f, 70.0f, 50.0f, 38, 97, 127)));
