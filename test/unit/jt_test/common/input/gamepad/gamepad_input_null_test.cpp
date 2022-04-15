#include <input/gamepad/gamepad_input_null.hpp>
#include <gtest/gtest.h>

TEST(GamepadInputNullTest, UpdateDoesNotThrow)
{
    jt::GamepadInputNull gp;
    ASSERT_NO_THROW(gp.update());
}

TEST(GamepadInputNullTest, ResetDoesNotThrow)
{
    jt::GamepadInputNull gp;
    ASSERT_NO_THROW(gp.reset());
}

class GamepadInputNullAxisTestFixture : public ::testing::TestWithParam<jt::GamepadAxisCode> {
};

TEST_P(GamepadInputNullAxisTestFixture, AxisRawReturns0)
{
    jt::GamepadInputNull gp;
    jt::Vector2f const expected = jt::Vector2f { 0.0f, 0.0f };
    ASSERT_EQ(gp.getAxisRaw(GetParam()), expected);
}
TEST_P(GamepadInputNullAxisTestFixture, AxisReturns0)
{
    jt::GamepadInputNull gp;
    jt::Vector2f const expected = jt::Vector2f { 0.0f, 0.0f };
    ASSERT_EQ(gp.getAxis(GetParam()), expected);
}

INSTANTIATE_TEST_SUITE_P(GamepadInputNullAxisTest, GamepadInputNullAxisTestFixture,
    ::testing::Values(jt::GamepadAxisCode::ARight, jt::GamepadAxisCode::ALeft));

class GamepadInputNullButtonTestFixture : public ::testing::TestWithParam<jt::GamepadButtonCode> {
};

TEST_P(GamepadInputNullButtonTestFixture, ButtonPressedReturnsFalse)
{
    jt::GamepadInputNull gp;
    ASSERT_FALSE(gp.pressed(GetParam()));
}

TEST_P(GamepadInputNullButtonTestFixture, ButtonJustPressedReturnsFalse)
{
    jt::GamepadInputNull gp;
    ASSERT_FALSE(gp.justPressed(GetParam()));
}

TEST_P(GamepadInputNullButtonTestFixture, ButtonReleasedReturnsFalse)
{
    jt::GamepadInputNull gp;
    ASSERT_FALSE(gp.released(GetParam()));
}

TEST_P(GamepadInputNullButtonTestFixture, ButtonJustReleasedReturnsFalse)
{
    jt::GamepadInputNull gp;
    ASSERT_FALSE(gp.justReleased(GetParam()));
}

INSTANTIATE_TEST_SUITE_P(GamepadInputNullButtonTest, GamepadInputNullButtonTestFixture,
    ::testing::Values(jt::GamepadButtonCode::GBA, jt::GamepadButtonCode::GBB,
        jt::GamepadButtonCode::GBX, jt::GamepadButtonCode::GBY, jt::GamepadButtonCode::GBStart,
        jt::GamepadButtonCode::GBBack, jt::GamepadButtonCode::GBRightStick,
        jt::GamepadButtonCode::GBLeftStick, jt::GamepadButtonCode::GBLB,
        jt::GamepadButtonCode::GBRB));
