#include <backend_setup.hpp>
#include <color/color_modifications.hpp>
#include <color/palette_builder.hpp>
#include <gtest/gtest.h>

TEST(PaletteBuilderTest, EmptyPalette)
{
    jt::PaletteBuilder builder;
    auto const pal = builder.create();
    ASSERT_TRUE(pal.empty());
}

TEST(PaletteBuilderTest, AddOneColor)
{
    jt::PaletteBuilder builder;
    auto const pal = builder.addColor(jt::colors::Blue).create();
    ASSERT_EQ(pal.getColor(0), jt::colors::Blue);
}

TEST(PaletteBuilderTest, AddTwoColors)
{
    jt::PaletteBuilder builder;
    auto const pal = builder.addColor(jt::colors::Blue).addColor(jt::colors::White).create();
    ASSERT_EQ(pal.getColor(0), jt::colors::Blue);
    ASSERT_EQ(pal.getColor(1), jt::colors::White);
}

TEST(PaletteBuilderTest, FromHEmpty)
{
    jt::PaletteBuilder builder;
    auto const pal = builder.addGradientH(0.0f, 0.0f, 0.0f, 0.0f, 0u).create();
    ASSERT_TRUE(pal.empty());
}

TEST(PaletteBuilderTest, FromHOneEntryBlack)
{
    jt::PaletteBuilder builder;
    auto const pal = builder.addGradientH(0.0f, 0.0f, 0.0f, 0.0f, 1u).create();
    ASSERT_EQ(pal.size(), 1u);

    auto col = pal.getColor(0);
    ASSERT_EQ(col, jt::colors::Black);
}

TEST(PaletteBuilderTest, FromHOneEntryRed)
{
    jt::PaletteBuilder builder;
    auto const pal = builder.addGradientH(0.0f, 0.0f, 100.0f, 100.0f, 1u).create();
    ASSERT_EQ(pal.size(), 1u);

    auto col = pal.getColor(0);
    ASSERT_EQ(col, jt::colors::Red);
}

TEST(PaletteBuilderTest, FromSOneEntryBlack)
{
    jt::PaletteBuilder builder;
    auto const pal = builder.addGradientS(0.0f, 0.0f, 0.0f, 0.0f, 1u).create();
    ASSERT_EQ(pal.size(), 1u);

    auto col = pal.getColor(0);
    ASSERT_EQ(col, jt::colors::Black);
}

TEST(PaletteBuilderTest, FromSOneEntryRed)
{
    jt::PaletteBuilder builder;
    auto const pal = builder.addGradientS(0.0f, 100.0f, 100.0f, 100.0f, 1u).create();
    ASSERT_EQ(pal.size(), 1u);

    auto col = pal.getColor(0);
    ASSERT_EQ(col, jt::colors::Red);
}

TEST(PaletteBuilderTest, FromVOneEntryBlack)
{
    jt::PaletteBuilder builder;
    auto const pal = builder.addGradientV(0.0f, 0.0f, 0.0f, 0.0f, 1u).create();
    ASSERT_EQ(pal.size(), 1u);

    auto col = pal.getColor(0);
    ASSERT_EQ(col, jt::colors::Black);
}

TEST(PaletteBuilderTest, FromVOneEntryRed)
{
    jt::PaletteBuilder builder;
    auto const pal = builder.addGradientV(0.0f, 100.0f, 100.0f, 100.0f, 1u).create();
    ASSERT_EQ(pal.size(), 1u);

    auto col = pal.getColor(0);
    ASSERT_EQ(col, jt::colors::Red);
}

class PaletteBuilderSizeTestFixture : public ::testing::TestWithParam<std::size_t> {
public:
    jt::PaletteBuilder builder;
};

TEST_P(PaletteBuilderSizeTestFixture, FromHSize)
{
    auto const expectedSize = GetParam();
    auto const pal = builder.addGradientH(0.0f, 0.0f, 0.0f, 0.0f, expectedSize).create();
    ASSERT_EQ(pal.size(), expectedSize);
}

TEST_P(PaletteBuilderSizeTestFixture, FromSSize)
{
    auto const expectedSize = GetParam();
    auto const pal = builder.addGradientS(0.0f, 0.0f, 0.0f, 0.0f, expectedSize).create();
    ASSERT_EQ(pal.size(), expectedSize);
}

TEST_P(PaletteBuilderSizeTestFixture, FromVSize)
{
    auto const expectedSize = GetParam();
    auto const pal = builder.addGradientV(0.0f, 0.0f, 0.0f, 0.0f, expectedSize).create();
    ASSERT_EQ(pal.size(), expectedSize);
}

INSTANTIATE_TEST_SUITE_P(
    PaletteBuilderSizeTest, PaletteBuilderSizeTestFixture, ::testing::Values(0u, 1u, 5u, 100u));

TEST(PaletteBuilderParseGPL, GPLWithOneEntry)
{
    auto const input = R"(GIMP Palette
#Palette Name: MS Paint Basic
#Description: The "Basic" Palette Used In The Program, MS Paint
#Colors: 1
64	0	64	400040

)";
    jt::PaletteBuilder builder;
    jt::Palette const pal = builder.addColorsFromGPL(input).create();
    jt::Color const expectedColor { 64, 0, 64 };
    ASSERT_EQ(pal.getColor(0), expectedColor);
}

TEST(PaletteBuilderParseGPL, GPLWithInvalidEntry)
{
    auto const input = R"(GIMP Palette
#Palette Name: MS Paint Basic
#Description: The "Basic" Palette Used In The Program, MS Paint
#Colors: 1
64	0	64	400040 1234

)";

    jt::PaletteBuilder builder;
    ASSERT_THROW((void)builder.addColorsFromGPL(input), std::invalid_argument);
}

TEST(PaletteBuilderParseGPL, GPLWithMultipleEntries)
{
    auto const input = R"(GIMP Palette
#Palette Name: MS Paint Basic
#Description: The "Basic" Palette Used In The Program
#Colors: 1
64	0	64	400040
128	255	255	80ffff
0	64	128	004080

)";

    jt::PaletteBuilder builder;
    jt::Palette const pal = builder.addColorsFromGPL(input).create();
    jt::Color const expectedColor0 { 64, 0, 64 };
    jt::Color const expectedColor1 { 128, 255, 255 };
    jt::Color const expectedColor2 { 0, 64, 128 };
    ASSERT_EQ(pal.getColor(0), expectedColor0);
    ASSERT_EQ(pal.getColor(1), expectedColor1);
    ASSERT_EQ(pal.getColor(2), expectedColor2);
}

TEST(PaletteBuilderTest, AddFromSprite)
{
    jt::PaletteBuilder builder;
    jt::TextureManagerInterface& tm { getTextureManager() };
    jt::Sprite sprite { "assets/test/unit/jt_test/coin.png", jt::Recti { 0, 0, 16, 16 }, tm };

    auto const palette = builder.addColorsFromPicture(sprite).create();
    ASSERT_EQ(palette.size(), 5u);
    jt::Color const expectedColor0 { 0, 0, 0, 0 };
    jt::Color const expectedColor1 { 0, 0, 0, 255 };
    jt::Color const expectedColor2 { 211, 172, 99 };
    jt::Color const expectedColor3 { 207, 149, 39 };
    jt::Color const expectedColor4 { 212, 193, 156 };
    ASSERT_EQ(palette.getColor(0), expectedColor0);
    ASSERT_EQ(palette.getColor(1), expectedColor1);
    ASSERT_EQ(palette.getColor(2), expectedColor2);
    ASSERT_EQ(palette.getColor(3), expectedColor3);
    ASSERT_EQ(palette.getColor(4), expectedColor4);
}

TEST(PaletteBuilderTest, AddFromAseprite)
{
    jt::PaletteBuilder builder;

    auto const palette
        = builder.addColorsFromAseprite("assets/test/unit/jt_test/dino_salto.aseprite").create();

    ASSERT_EQ(palette.size(), 22u);

    jt::Color const expectedColor0 { 0, 0, 0, 255 };
    jt::Color const expectedColor1 { 32, 59, 32 };
    jt::Color const expectedColor20 { 128, 82, 56, 255 };
    ASSERT_EQ(palette.getColor(0), expectedColor0);
    ASSERT_EQ(palette.getColor(1), expectedColor1);
    ASSERT_EQ(palette.getColor(20), expectedColor20);
}

TEST(PaletteBuilderTest, MakeUnique)
{
    jt::PaletteBuilder builder;
    auto const palette = builder.addColor(jt::Color { 0, 0, 0, 255 })
                             .addColor(jt::Color { 0, 0, 0, 255 })
                             .addColor(jt::Color { 255, 255, 255, 255 })
                             .addColor(jt::Color { 0, 255, 0, 255 })
                             .addColor(jt::Color { 255, 255, 255, 255 })
                             .addColor(jt::Color { 0, 0, 0, 255 })
                             .makeUnique()
                             .create();
    ASSERT_EQ(palette.size(), 3u);
    jt::Color const expectedColor0 { 0, 0, 0, 255 };
    jt::Color const expectedColor1 { 255, 255, 255, 255 };
    jt::Color const expectedColor2 { 0, 255, 0, 255 };
    ASSERT_EQ(palette.getColor(0), expectedColor0);
    ASSERT_EQ(palette.getColor(1), expectedColor1);
    ASSERT_EQ(palette.getColor(2), expectedColor2);
}

TEST(PaletteBuilderTest, ApplyFunction)
{
    jt::PaletteBuilder builder;
    auto const palette = builder.addColor(jt::colors::Red)
                             .addColor(jt::colors::Green)
                             .addColor(jt::colors::Blue)
                             .applyToPalette(jt::ColorModifications::complement)
                             .create();
    ASSERT_EQ(palette.size(), 3u);
    ASSERT_EQ(palette.getColor(0), jt::colors::Cyan);
    ASSERT_EQ(palette.getColor(1), jt::colors::Magenta);
    ASSERT_EQ(palette.getColor(2), jt::colors::Yellow);
}
