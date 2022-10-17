#include <color/palette.hpp>
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

TEST(PaletteTest, ConstructorResultsInCorrectSize1)
{
    jt::Palette const pal { { jt::colors::Black } };
    ASSERT_EQ(pal.size(), 1U);
}

TEST(PaletteTest, ConstructorResultsInCorrectSize2)
{
    jt::Palette const pal { { jt::colors::Black, jt::colors::White } };
    ASSERT_EQ(pal.size(), 2U);
}

TEST(PaletteTest, ConstructorInitialEmpty)
{
    jt::Palette const pal { { jt::colors::Black, jt::colors::White } };
    ASSERT_FALSE(pal.empty());
}
