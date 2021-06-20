#include "keyboard_input.hpp"
#include "gtest/gtest.h"

TEST(KeyboardInput, AllKeysAlwaysPressed)
{
    jt::KeyboardInput keyboardInput { [](auto /*b*/) { return true; } };
    keyboardInput.updateKeys();
    for (auto const k : jt::getAllKeys()) {
        EXPECT_TRUE(keyboardInput.pressed(k));
        EXPECT_FALSE(keyboardInput.released(k));
    }
}

TEST(KeyboardInput, AllButtonsAlwaysReleased)
{
    jt::KeyboardInput keyboardInput { [](auto /*b*/) { return false; } };
    keyboardInput.updateKeys();
    for (auto const k : jt::getAllKeys()) {
        EXPECT_FALSE(keyboardInput.pressed(k));
        EXPECT_TRUE(keyboardInput.released(k));
    }
}

TEST(KeyboardInput, AllButtonsJustPressed)
{
    jt::KeyboardInput keyboardInput { [](auto /*b*/) { return true; } };
    keyboardInput.reset();
    keyboardInput.updateKeys();
    for (auto const k : jt::getAllKeys()) {
        EXPECT_TRUE(keyboardInput.justPressed(k));
        EXPECT_FALSE(keyboardInput.justReleased(k));
    }
    keyboardInput.updateKeys();
    for (auto const k : jt::getAllKeys()) {
        EXPECT_FALSE(keyboardInput.justPressed(k));
        EXPECT_FALSE(keyboardInput.justReleased(k));
    }
}

TEST(KeyboardInput, AllButtonsJustReleased)
{
    int call_count { 0 };
    // return true on first call, false otherwise
    jt::KeyboardInput keyboardInput { [&call_count](auto /*b*/) {
        auto v = (call_count == 0);
        return v;
    } };

    keyboardInput.reset();
    keyboardInput.updateKeys();
    call_count++;
    for (auto const k : jt::getAllKeys()) {
        ASSERT_TRUE(keyboardInput.justPressed(k));
        ASSERT_FALSE(keyboardInput.justReleased(k));
    }
    keyboardInput.updateKeys();
    for (auto const k : jt::getAllKeys()) {
        EXPECT_FALSE(keyboardInput.justPressed(k));
        EXPECT_TRUE(keyboardInput.justReleased(k));
    }
}
