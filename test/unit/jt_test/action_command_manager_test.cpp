#include "action_commands/action_command_manager.hpp"
#include "logging/logger_null.hpp"
#include <gtest/gtest.h>

TEST(ActionCommandManagerTest, Instantiate)
{
    jt::null_objects::LoggerNull logger;

    ASSERT_NO_THROW(jt::ActionCommandManager { logger });
}

TEST(ActionCommandManagerTest, ExecuteEmptyCommand)
{
    jt::null_objects::LoggerNull logger;

    jt::ActionCommandManager manager { logger };
    manager.executeCommand("");
}

TEST(ActionCommandManagerTest, GetAllCommandsInitial)
{
    jt::null_objects::LoggerNull logger;

    jt::ActionCommandManager manager { logger };
    ASSERT_TRUE(manager.getAllCommands().empty());
}

TEST(ActionCommandManagerTest, GetAllCommandsAfterRegisterCommand)
{
    jt::null_objects::LoggerNull logger;

    jt::ActionCommandManager manager { logger };

    auto command = [](auto /*unused*/) {};
    manager.registerTemporaryCommand("bla", command);
    ASSERT_FALSE(manager.getAllCommands().empty());
}

TEST(ActionCommandManagerTest, GetAllCommandsAfterUpdate)
{
    jt::null_objects::LoggerNull logger;

    jt::ActionCommandManager manager { logger };

    auto command = [](auto /*unused*/) {};
    manager.registerTemporaryCommand("bla", command);
    manager.update();
    ASSERT_TRUE(manager.getAllCommands().empty());
}

TEST(ActionCommandManagerTest, GetAllCommandsAfterUpdateWhenStored)
{
    jt::null_objects::LoggerNull logger;

    jt::ActionCommandManager manager { logger };

    auto command = [](auto /*unused*/) {};
    auto sharedState = manager.registerTemporaryCommand("bla", command);
    manager.update();
    ASSERT_FALSE(manager.getAllCommands().empty());
}

TEST(ActionCommandManagerTest, ExecuteNonExistingCommand)
{
    jt::null_objects::LoggerNull logger;

    jt::ActionCommandManager manager { logger };
    manager.executeCommand("a b c 1 2 3");
}
