#include "palette.hpp"
#include <gtest/gtest.h>

TEST(PaletteTest, InitialSizeIsZero)
{
    jt::Palette pal;
    ASSERT_EQ(pal.size(), 0U);
}

TEST(PaletteTest, InitialEmpty)
{
    jt::Palette pal;
    ASSERT_TRUE(pal.empty());
}

TEST(PaletteTest, ConstructorInitialSize)
{
    jt::Palette pal { { jt::colors::Black, jt::colors::White } };
    ASSERT_EQ(pal.size(), 2U);
}

TEST(PaletteTest, ConstructorInitialEmpty)
{
    jt::Palette pal { { jt::colors::Black, jt::colors::White } };
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
