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
    ASSERT_EQ(c.r(), 0);
    ASSERT_EQ(c.g(), 111);
    ASSERT_EQ(c.b(), 222);
}
