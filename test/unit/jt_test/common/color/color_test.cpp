#include <color/color.hpp>
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

TEST(ColorTest, IsEqualReturnsTrueForSameColor)
{
    jt::Color const color { 1, 2, 3 };
    ASSERT_TRUE(color == color);
}

TEST(ColorTest, IsEqualReturnsFalseForSameColor)
{
    jt::Color const color1 { 1, 2, 3 };
    jt::Color const color2 { 4, 5, 6 };
    ASSERT_FALSE(color1 == color2);
}
