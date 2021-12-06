#include "console/log.hpp"
#include <gtest/gtest.h>

using jt::Log;

TEST(LogTest, GetCompleteLogIsEmptyByDefault)
{
    Log l;
    ASSERT_TRUE(l.getAllLogs().empty());
}

TEST(LogTest, GetCompleteLogAfterDebug)
{
    Log l;
    l.debug("test1234");

    auto entry = l.getAllLogs().at(0);

    // TODO Add comparison operator for LogEntry
    ASSERT_EQ(entry.message, "test1234");
    ASSERT_EQ(entry.level, LogLevel::LogLevelDebug);
}

TEST(LogTest, GetCompleteLogAfterVerbose)
{
    Log l;
    l.verbose("abc");

    auto entry = l.getAllLogs().at(0);

    // TODO Add comparison operator for LogEntry
    ASSERT_EQ(entry.message, "abc");
    ASSERT_EQ(entry.level, LogLevel::LogLevelVerbose);
}

TEST(LogTest, GetCompleteLogAfterError)
{
    Log l;
    l.error("errno");

    auto entry = l.getAllLogs().at(0);

    // TODO Add comparison operator for LogEntry
    ASSERT_EQ(entry.message, "errno");
    ASSERT_EQ(entry.level, LogLevel::LogLevelError);
}
