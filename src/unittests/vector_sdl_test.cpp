#include "vector.hpp"
#include <gtest/gtest.h>

TEST(Vector2U, TosdlVector)
{
    jt::Vector2u vec { 4, 5 };
    SDL_Point expected { 4, 5 };
    SDL_Point value = vec;
    EXPECT_EQ(expected, value);
}
