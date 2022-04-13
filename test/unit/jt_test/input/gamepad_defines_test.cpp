#include <input/gamepad/gamepad_defines.hpp>
#include <gtest/gtest.h>

TEST(GamepadDefinesTest, GetAllGamepadButtonsReturnsCorrectSize)
{
    ASSERT_EQ(jt::getAllGamepadButtons().size(), 18);
}

TEST(GamepadDefinesTest, GetAllGamepadAxisReturnsCorrectSize)
{
    ASSERT_EQ(jt::getAllAxis().size(), 2);
}
