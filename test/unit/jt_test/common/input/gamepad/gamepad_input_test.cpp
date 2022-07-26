#include <input/gamepad/gamepad_input.hpp>
#include <gtest/gtest.h>

TEST(GamepadInputTest, GetAxisRawReturnsGivenValue)
{
    jt::Vector2f expectedValue { 1.0f, 1.0f };
    jt::GamepadInput gamepad { 0,
        [&expectedValue](jt::GamepadAxisCode /*axis*/) { return expectedValue; },
        [](jt::GamepadButtonCode /*button*/) { return false; } };

    ASSERT_EQ(gamepad.getAxisRaw(jt::GamepadAxisCode::ALeft), expectedValue);
    expectedValue.x = 50.0f;
    expectedValue.y = -42.0f;
    ASSERT_EQ(gamepad.getAxisRaw(jt::GamepadAxisCode::ALeft), expectedValue);
}

TEST(GamepadInputTest, GetAxisReturnsZeroForValueSmallerDeadZone)
{
    jt::GamepadInput gamepad { 0,
        [](jt::GamepadAxisCode /*axis*/) {
            return jt::Vector2f { 1.0f, 1.0f };
        },
        [](jt::GamepadButtonCode /*button*/) { return false; } };

    jt::Vector2f const expectedValue { 0.0f, 0.0f };
    ASSERT_EQ(gamepad.getAxis(jt::GamepadAxisCode::ALeft), expectedValue);
}

TEST(GamepadInputTest, GetAxisReturnsCorrectValueForXValueOutOfDeadZone)
{
    jt::GamepadInput gamepad { 0,
        [](jt::GamepadAxisCode /*axis*/) {
            return jt::Vector2f { 15.0f, 0.0f };
        },
        [](jt::GamepadButtonCode /*button*/) { return false; } };

    jt::Vector2f const expectedValue { 0.15f, 0.0f };
    ASSERT_EQ(gamepad.getAxis(jt::GamepadAxisCode::ALeft), expectedValue);
}

TEST(GamepadInputTest, GetAxisReturnsCorrectValueForYValueOutOfDeadZone)
{
    jt::GamepadInput gamepad { 0,
        [](jt::GamepadAxisCode /*axis*/) {
            return jt::Vector2f { 0.0f, 15.0f };
        },
        [](jt::GamepadButtonCode /*button*/) { return false; } };

    jt::Vector2f const expectedValue { 0.0f, 0.15f };
    ASSERT_EQ(gamepad.getAxis(jt::GamepadAxisCode::ALeft), expectedValue);
}

TEST(GamepadInputTest, ButtonPressedReturnsFalseIfButtonNotPressed)
{
    jt::GamepadInput gamepad { 0,
        [](jt::GamepadAxisCode /*axis*/) {
            return jt::Vector2f { 0.0f, 0.0f };
        },
        [](jt::GamepadButtonCode /*button*/) { return false; } };

    gamepad.update();

    for (auto b : jt::getAllGamepadButtons()) {
        ASSERT_FALSE(gamepad.pressed(b));
    }
}

TEST(GamepadInputTest, ButtonPressedReturnsTrueIfButtonPressed)
{
    jt::GamepadInput gamepad { 0,
        [](jt::GamepadAxisCode /*axis*/) {
            return jt::Vector2f { 0.0f, 0.0f };
        },
        [](jt::GamepadButtonCode /*button*/) { return true; } };

    gamepad.update();

    for (auto b : jt::getAllGamepadButtons()) {
        ASSERT_TRUE(gamepad.pressed(b));
    }
}

TEST(GamepadInputTest, ButtonReleasedReturnsTrueIfButtonNotPressed)
{
    jt::GamepadInput gamepad { 0,
        [](jt::GamepadAxisCode /*axis*/) {
            return jt::Vector2f { 0.0f, 0.0f };
        },
        [](jt::GamepadButtonCode /*button*/) { return false; } };

    gamepad.update();

    for (auto b : jt::getAllGamepadButtons()) {
        ASSERT_TRUE(gamepad.released(b));
    }
}

TEST(GamepadInputTest, ButtonJustPressedReturnsTrueIfButtonPressed)
{
    jt::GamepadInput gamepad { 0,
        [](jt::GamepadAxisCode /*axis*/) {
            return jt::Vector2f { 0.0f, 0.0f };
        },
        [](jt::GamepadButtonCode /*button*/) { return true; } };

    gamepad.update();

    for (auto b : jt::getAllGamepadButtons()) {
        ASSERT_TRUE(gamepad.justPressed(b));
    }
}

TEST(GamepadInputTest, ButtonJustReleasedReturnsFalseIfButtonNotReleased)
{
    jt::GamepadInput gamepad { 0,
        [](jt::GamepadAxisCode /*axis*/) {
            return jt::Vector2f { 0.0f, 0.0f };
        },
        [](jt::GamepadButtonCode /*button*/) { return false; } };

    gamepad.update();

    for (auto b : jt::getAllGamepadButtons()) {
        ASSERT_FALSE(gamepad.justReleased(b));
    }
}

TEST(GamepadInputTest, LibAxisValue)
{
    jt::Vector2f const expectedValue { 0.0f, 0.0f };
    ASSERT_EQ(jt::libAxisValue(0, jt::GamepadAxisCode::ARight), expectedValue);
}
