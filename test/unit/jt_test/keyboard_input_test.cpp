#include "input/keyboard_input.hpp"
#include "gtest/gtest.h"
#include "command_recorder.hpp"

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

TEST(KeyboardInput, CommandExecutedForPressed)
{
    jt::KeyboardInput keyboardInput { [](auto /*b*/) { return true; } };
    std::shared_ptr<CommandRecorder> command = std::make_shared<CommandRecorder>();
    keyboardInput.setCommandPressed({ jt::KeyCode::Space }, command);
    keyboardInput.updateKeys();
    keyboardInput.updateCommands(1.0f);

    ASSERT_TRUE(command->m_executed);
}

TEST(KeyboardInput, CommandExecutedForReleased)
{
    jt::KeyboardInput keyboardInput { [](auto /*b*/) { return false; } };
    std::shared_ptr<CommandRecorder> command = std::make_shared<CommandRecorder>();
    keyboardInput.setCommandReleased({ jt::KeyCode::Space }, command);
    keyboardInput.updateKeys();
    keyboardInput.updateCommands(1.0f);

    ASSERT_TRUE(command->m_executed);
}

TEST(KeyboardInput, CommandExecutedForJustPressed)
{
    jt::KeyboardInput keyboardInput { [](auto /*b*/) { return true; } };
    std::shared_ptr<CommandRecorder> command = std::make_shared<CommandRecorder>();
    keyboardInput.reset();
    keyboardInput.setCommandJustPressed({ jt::KeyCode::Space }, command);
    keyboardInput.updateKeys();
    keyboardInput.updateCommands(1.0f);
    ASSERT_TRUE(command->m_executed);
}

TEST(KeyboardInput, CommandExecutedForJustReleased)
{
    int call_count { 0 };
    // return true on first call, false otherwise
    jt::KeyboardInput keyboardInput { [&call_count](auto /*b*/) {
        auto v = (call_count == 0);
        return v;
    } };

    keyboardInput.reset();

    std::shared_ptr<CommandRecorder> command = std::make_shared<CommandRecorder>();
    keyboardInput.setCommandJustReleased({ jt::KeyCode::Space }, command);

    keyboardInput.updateKeys();
    keyboardInput.updateCommands(1.0f);
    call_count++;
    keyboardInput.updateKeys();
    keyboardInput.updateCommands(1.0f);
    ASSERT_TRUE(command->m_executed);
}
