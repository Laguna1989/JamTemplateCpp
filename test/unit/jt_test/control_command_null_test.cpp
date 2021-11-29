#include "input/control_command_null.hpp"
#include <gtest/gtest.h>

TEST(ControlCommandNullTest, Execute)
{
    jt::ControlCommandNull command;
    ASSERT_NO_THROW(command.execute(1.0f));
}

TEST(ControlCommandNullTest, Reset)
{
    jt::ControlCommandNull command;
    ASSERT_NO_THROW(command.reset());
}
