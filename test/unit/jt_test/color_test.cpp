#include "color.hpp"
#include <gtest/gtest.h>
#include <type_traits>

TEST(ColorTest, IsDefaultConstructible)
{
    ASSERT_TRUE(std::is_default_constructible<jt::Color>::value);
}

TEST(ColorTest, InitialValues)
{
    jt::Color c {};
    ASSERT_EQ(c, jt::colors::Black);
}

TEST(ColorTest, SetValues)
{
    jt::Color c { 0, 111, 222 };
    ASSERT_EQ(c.r, 0);
    ASSERT_EQ(c.g, 111);
    ASSERT_EQ(c.b, 222);
}

TEST(ColorTest, FromRGB)
{
    auto c = jt::MakeColor::FromRGB(1, 2, 3);
    ASSERT_EQ(c.r, 1);
    ASSERT_EQ(c.g, 2);
    ASSERT_EQ(c.b, 3);
    ASSERT_EQ(c.a, 255);
}

TEST(ColorTest, FromRGBA)
{
    auto c = jt::MakeColor::FromRGBA(1, 2, 3, 4);
    ASSERT_EQ(c.r, 1);
    ASSERT_EQ(c.g, 2);
    ASSERT_EQ(c.b, 3);
    ASSERT_EQ(c.a, 4);
}

TEST(ColorTest, FromHSV)
{
    auto c = jt::MakeColor::FromHSV(0.0f, 100.0f, 100.0f);
    ASSERT_EQ(c.r, 255);
    ASSERT_EQ(c.g, 0);
    ASSERT_EQ(c.b, 0);
    ASSERT_EQ(c.a, 255);
}

TEST(ColorTest, FromHSVA)
{
    auto c = jt::MakeColor::FromHSVA(0.0f, 100.0f, 100.0f, 25);
    ASSERT_EQ(c.r, 255);
    ASSERT_EQ(c.g, 0);
    ASSERT_EQ(c.b, 0);
    ASSERT_EQ(c.a, 25);
}

TEST(ColorTest, FromHexString)
{
    auto c = jt::MakeColor::FromHexString("ac3232");
    ASSERT_EQ(c.r, 172);
    ASSERT_EQ(c.g, 50);
    ASSERT_EQ(c.b, 50);
    ASSERT_EQ(c.a, 255);
}

TEST(ColorTest, FromHexStringCapsAndHash)
{
    auto c = jt::MakeColor::FromHexString("#FF00FF");
    ASSERT_EQ(c.r, 255);
    ASSERT_EQ(c.g, 0);
    ASSERT_EQ(c.b, 255);
    ASSERT_EQ(c.a, 255);
}

TEST(ColorTest, FromHexStringInvalid)
{
    ASSERT_THROW(jt::MakeColor::FromHexString("#FF00FF1234XXXs"), std::invalid_argument);
}
