#include <log/log_level.hpp>
#include <log/log_target_ostream.hpp>
#include <log/logger_null.hpp>
#include <gtest/gtest.h>

TEST(LoggerNullTest, LogActionsDoNothing)
{
    jt::null_objects::LoggerNull logger;

    ASSERT_NO_THROW(logger.action("abcd"));
    ASSERT_NO_THROW(logger.fatal("abcd"));
    ASSERT_NO_THROW(logger.error("abcd"));
    ASSERT_NO_THROW(logger.warning("abcd"));
    ASSERT_NO_THROW(logger.info("abcd"));
    ASSERT_NO_THROW(logger.debug("abcd"));
    ASSERT_NO_THROW(logger.verbose("abcd"));
}

TEST(LoggerNullTest, AddNullPtrLogTargetDoesNothing)
{
    jt::null_objects::LoggerNull logger;

    ASSERT_NO_THROW(logger.addLogTarget(nullptr));
}

TEST(LoggerNullTest, AddValidLogTargetDoesNothing)
{
    jt::null_objects::LoggerNull logger;

    ASSERT_NO_THROW(logger.addLogTarget(std::make_shared<jt::LogTargetOstream>()));
}

TEST(LoggerNullTest, SetLogLevelDoesNothing)
{
    jt::null_objects::LoggerNull logger;
    ASSERT_NO_THROW(logger.setLogLevel(jt::LogLevel::Fatal));
}
