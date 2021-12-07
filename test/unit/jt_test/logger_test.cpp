#include "logging/logger.hpp"
#include <gtest/gtest.h>

using jt::Logger;

TEST(LogTest, GetCompleteLogIsEmptyByDefault)
{
    Logger l;
    ASSERT_TRUE(l.getHistory().empty());
}

TEST(LogTest, GetCompleteLogAfterLog)
{
    Logger l;
    l.debug("bla");

    // TODO Add comparison operator for LogEntry
    ASSERT_EQ(l.getHistory().at(0).message, "bla");
    ASSERT_EQ(l.getHistory().at(0).level, LogLevel::LogLevelDebug);
}
