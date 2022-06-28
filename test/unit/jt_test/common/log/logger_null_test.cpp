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

TEST(LoggerNullTest, HistoryIsEmptyInitially)
{
    jt::null_objects::LoggerNull logger;
    ASSERT_TRUE(logger.getHistory().empty());
}

TEST(LoggerNullTest, HistoryIsEmptyAfterLogging)
{
    jt::null_objects::LoggerNull logger;
    logger.fatal("test");
    ASSERT_TRUE(logger.getHistory().empty());
}

TEST(LoggerNullTest, SetLogLevelDoesNothing)
{
    jt::null_objects::LoggerNull logger;
    ASSERT_NO_THROW(logger.setLogLevel(LogLevel::LogLevelFatal));
}

TEST(LoggerNullTest, ClearDoesNothing)
{
    jt::null_objects::LoggerNull logger;
    ASSERT_NO_THROW(logger.clear());
}
