#include "vector.hpp"
#include <gtest/gtest.h>

TEST(Vector2USFML, ToSfVector)
{
    jt::Vector2u vec { 4, 5 };
    sf::Vector2u expected { 4, 5 };
    sf::Vector2u value = vec;
    EXPECT_EQ(expected, value);
}
