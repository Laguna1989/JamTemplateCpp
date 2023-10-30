#include <input/input_manager_null.hpp>
#include <gtest/gtest.h>

TEST(InputManagerNullTest, ReturnsNullptrIfInstantiatedWithNullptr)
{
    jt::InputManagerNull im;
    ASSERT_NE(im.keyboard(), nullptr);
    ASSERT_NE(im.mouse(), nullptr);
}

TEST(InputManagerNullTest, GamepadReturnsNoNullptr)
{
    jt::InputManagerNull im {};
    ASSERT_NE(im.gamepad(0), nullptr);
    ASSERT_NE(im.gamepad(1), nullptr);
    ASSERT_NE(im.gamepad(2), nullptr);
    ASSERT_NE(im.gamepad(3), nullptr);
}

TEST(InputManagerNullTest, ResetWithNullptrs)
{
    jt::InputManagerNull im;
    ASSERT_NO_THROW(im.reset());
}

TEST(InputManagerNullTest, UpdateWithMocks)
{
    jt::InputManagerNull im;
    jt::MousePosition const mp { 1.0f, 2.0f, 3.0f, 4.0f };
    ASSERT_NO_THROW(im.update(false, false, mp, 0));
}

TEST(InputManagerNullTest, NumberOfGamepads)
{
    jt::InputManagerNull im;
    ASSERT_EQ(im.getNumberOfGamepads(), 0u);
}
