#include <log/log_entry.hpp>
#include <log/log_level.hpp>
#include <log/log_target_ostream.hpp>
#include <gtest/gtest.h>
#include <sstream>

TEST(LogTargetOstreamTest, LogsExpectedString)
{
    std::stringstream ss;
    jt::LogTargetOstream target { ss };

    auto const logMessage = "abcd";
    target.log(jt::LogEntry { logMessage, "time", jt::LogLevel::Action, {} });

    auto const expectedLogEntry = logMessage + std::string("\n");
    ASSERT_EQ(ss.str(), expectedLogEntry);
}

TEST(LogTargetOstreamTest, LogNothingIfLevelIsNotMet)
{
    std::stringstream ss;
    jt::LogTargetOstream target { ss };

    auto const logMessage = "abcd";
    target.setLogLevel(jt::LogLevel::Off);
    target.log(jt::LogEntry { logMessage, "time", jt::LogLevel::Verbose, {} });

    auto const expectedLogEntry = logMessage + std::string("\n");
    ASSERT_TRUE(ss.str().empty());
}

TEST(LogTargetOstreamTest, GetDefaultLogLevel)
{
    std::stringstream ss;
    jt::LogTargetOstream target { ss };

    ASSERT_EQ(target.getLogLevel(), jt::LogLevel::Verbose);
}

TEST(LogTargetOstreamTest, GetLogLevelAfterSet)
{
    std::stringstream ss;
    jt::LogTargetOstream target { ss };

    target.setLogLevel(jt::LogLevel::Fatal);
    ASSERT_EQ(target.getLogLevel(), jt::LogLevel::Fatal);
}
