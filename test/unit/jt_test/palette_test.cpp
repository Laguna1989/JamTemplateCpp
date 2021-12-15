#include "palette.hpp"
#include <gtest/gtest.h>

TEST(PaletteTest, InitialSizeIsZero)
{
    jt::Palette const pal;
    ASSERT_EQ(pal.size(), 0U);
}

TEST(PaletteTest, InitialEmpty)
{
    jt::Palette const pal;
    ASSERT_TRUE(pal.empty());
}

TEST(PaletteTest, ConstructorInitialSize)
{
    jt::Palette const pal { { jt::colors::Black, jt::colors::White } };
    ASSERT_EQ(pal.size(), 2U);
}

TEST(PaletteTest, ConstructorInitialEmpty)
{
    jt::Palette const pal { { jt::colors::Black, jt::colors::White } };
    ASSERT_FALSE(pal.empty());
}

TEST(PaletteTest, SizeAfterAdd)
{
    jt::Palette pal;
    pal = pal.addColor(jt::colors::Black);
    ASSERT_EQ(pal.size(), 1U);
}

TEST(PaletteTest, NotEmptyAfterAdd)
{
    jt::Palette pal;
    pal = pal.addColor(jt::colors::Black);
    ASSERT_FALSE(pal.empty());
}

TEST(PaletteTest, FromHEmpty)
{
    auto const pal = jt::Palette::createGradientH(0.0f, 0.0f, 0.0f, 0.0f, 0U);
    ASSERT_TRUE(pal.empty());
}

TEST(PaletteTest, FromHOneEntryBlack)
{
    auto const pal = jt::Palette::createGradientH(0.0f, 0.0f, 0.0f, 0.0f, 1U);
    ASSERT_EQ(pal.size(), 1U);

    auto col = pal.getColor(0);
    ASSERT_EQ(col, jt::colors::Black);
}

TEST(PaletteTest, FromHOneEntryRed)
{
    auto const pal = jt::Palette::createGradientH(0.0f, 0.0f, 100.0f, 100.0f, 1U);
    ASSERT_EQ(pal.size(), 1U);

    auto col = pal.getColor(0);
    ASSERT_EQ(col, jt::colors::Red);
}

TEST(PaletteTest, FromSOneEntryBlack)
{
    auto const pal = jt::Palette::createGradientS(0.0f, 0.0f, 0.0f, 0.0f, 1U);
    ASSERT_EQ(pal.size(), 1U);

    auto col = pal.getColor(0);
    ASSERT_EQ(col, jt::colors::Black);
}

TEST(PaletteTest, FromSOneEntryRed)
{
    auto const pal = jt::Palette::createGradientS(0.0f, 100.0f, 100.0f, 100.0f, 1U);
    ASSERT_EQ(pal.size(), 1U);

    auto col = pal.getColor(0);
    ASSERT_EQ(col, jt::colors::Red);
}

TEST(PaletteTest, FromVOneEntryBlack)
{
    auto const pal = jt::Palette::createGradientV(0.0f, 0.0f, 0.0f, 0.0f, 1U);
    ASSERT_EQ(pal.size(), 1U);

    auto col = pal.getColor(0);
    ASSERT_EQ(col, jt::colors::Black);
}

TEST(PaletteTest, FromVOneEntryRed)
{
    auto const pal = jt::Palette::createGradientV(0.0f, 100.0f, 100.0f, 100.0f, 1U);
    ASSERT_EQ(pal.size(), 1U);

    auto col = pal.getColor(0);
    ASSERT_EQ(col, jt::colors::Red);
}

class PaletteSizeTestFixture : public ::testing::TestWithParam<std::size_t> {
};

TEST_P(PaletteSizeTestFixture, FromHSize)
{
    auto const expectedSize = GetParam();
    auto const pal = jt::Palette::createGradientH(0.0f, 0.0f, 0.0f, 0.0f, expectedSize);
    ASSERT_EQ(pal.size(), expectedSize);
}

TEST_P(PaletteSizeTestFixture, FromSSize)
{
    auto const expectedSize = GetParam();
    auto const pal = jt::Palette::createGradientS(0.0f, 0.0f, 0.0f, 0.0f, expectedSize);
    ASSERT_EQ(pal.size(), expectedSize);
}

TEST_P(PaletteSizeTestFixture, FromVSize)
{
    auto const expectedSize = GetParam();
    auto const pal = jt::Palette::createGradientV(0.0f, 0.0f, 0.0f, 0.0f, expectedSize);
    ASSERT_EQ(pal.size(), expectedSize);
}

INSTANTIATE_TEST_SUITE_P(
    PaletteSizeTest, PaletteSizeTestFixture, ::testing::Values(0U, 1U, 5U, 100U));

TEST(PaletteParseGPL, GPLWithOneEntry)
{
    auto const input = R"(GIMP Palette
#Palette Name: MS Paint Basic
#Description: The "Basic" Palette Used In The Program, MS Paint 
#Colors: 1
64	0	64	400040

)";

    jt::Palette const pal = jt::Palette::parseGPL(input);
    ASSERT_EQ(pal.getColor(0), jt::MakeColor::FromRGB(64, 0, 64));
}

TEST(PaletteParseGPL, GPLWithInvalidEntry)
{
    auto const input = R"(GIMP Palette
#Palette Name: MS Paint Basic
#Description: The "Basic" Palette Used In The Program, MS Paint
#Colors: 1
64	0	64	400040 1234

)";

    ASSERT_THROW(jt::Palette::parseGPL(input), std::invalid_argument);
}

TEST(PaletteParseGPL, GPLWithMultipleEntries)
{
    auto const input = R"(GIMP Palette
#Palette Name: MS Paint Basic
#Description: The "Basic" Palette Used In The Program
#Colors: 1
64	0	64	400040
128	255	255	80ffff
0	64	128	004080

)";

    jt::Palette const pal = jt::Palette::parseGPL(input);
    ASSERT_EQ(pal.getColor(0), jt::MakeColor::FromRGB(64, 0, 64));
    ASSERT_EQ(pal.getColor(1), jt::MakeColor::FromRGB(128, 255, 255));
    ASSERT_EQ(pal.getColor(2), jt::MakeColor::FromRGB(0, 64, 128));
}
