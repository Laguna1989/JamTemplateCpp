#include <input/keyboard/keyboard_input_null.hpp>
#include <gtest/gtest.h>

TEST(KeyboardInputNullTest, UpdateKeysDoesNotThrow)
{
    jt::KeyboardInputNull kb;
    ASSERT_NO_THROW(kb.updateKeys());
}

TEST(KeyboardInputNullTest, UpdateCommandsDoesNotThrow)
{
    jt::KeyboardInputNull kb;
    ASSERT_NO_THROW(kb.updateCommands(0.1f));
}

TEST(KeyboardInputNullTest, SetCommandsDoesNotThrow)
{
    jt::KeyboardInputNull kb;

    ASSERT_NO_THROW(kb.setCommandPressed({ jt::KeyCode::A }, nullptr));
    ASSERT_NO_THROW(kb.setCommandJustPressed({ jt::KeyCode::A }, nullptr));
    ASSERT_NO_THROW(kb.setCommandReleased({ jt::KeyCode::A }, nullptr));
    ASSERT_NO_THROW(kb.setCommandJustReleased({ jt::KeyCode::A }, nullptr));
}

TEST(KeyboardInputNullTest, ResetDoesNotThrow)
{
    jt::KeyboardInputNull kb;
    ASSERT_NO_THROW(kb.reset());
}

TEST(KeyboardInputNullTest, PressedReturnsFalse)
{
    jt::KeyboardInputNull kb;
    for (auto& key : jt::getAllKeys()) {
        ASSERT_FALSE(kb.pressed(key));
    }
}

TEST(KeyboardInputNullTest, JustPressedReturnsFalse)
{
    jt::KeyboardInputNull kb;
    for (auto& key : jt::getAllKeys()) {
        ASSERT_FALSE(kb.justPressed(key));
    }
}
TEST(KeyboardInputNullTest, ReleasedReturnsFalse)
{
    jt::KeyboardInputNull kb;
    for (auto& key : jt::getAllKeys()) {
        ASSERT_FALSE(kb.released(key));
    }
}

TEST(KeyboardInputNullTest, JustReleasedReturnsFalse)
{
    jt::KeyboardInputNull kb;
    for (auto& key : jt::getAllKeys()) {
        ASSERT_FALSE(kb.justReleased(key));
    }
}
