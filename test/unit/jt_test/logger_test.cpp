#include "logging/logger.hpp"
#include "logging/logger_null.hpp"
#include <gtest/gtest.h>

template <typename T>
class LoggerTypedTestFixture : public ::testing::Test {
public:
    T logger;
};

using MyTypes = testing::Types<jt::Logger, jt::null_objects::LoggerNull>;
TYPED_TEST_SUITE(LoggerTypedTestFixture, MyTypes);

TYPED_TEST(LoggerTypedTestFixture, GetCompleteLogIsEmptyByDefault)
{
    ASSERT_TRUE(logger.getHistory().empty());
}

TYPED_TEST(LoggerTypedTestFixture, AddNullptrLogTarget)
{
    ASSERT_NO_THROW(logger.addLogTarget(nullptr));
}

TYPED_TEST(LoggerTypedTestFixture, ActionDoesNotRaiseException)
{
    ASSERT_NO_THROW(logger.action(""));
}

TYPED_TEST(LoggerTypedTestFixture, FatalDoesNotRaiseException)
{
    ASSERT_NO_THROW(logger.fatal(""));
}

TYPED_TEST(LoggerTypedTestFixture, ErrorDoesNotRaiseException)
{
    ASSERT_NO_THROW(logger.error(""));
}

TYPED_TEST(LoggerTypedTestFixture, WarnDoesNotRaiseException)
{
    ASSERT_NO_THROW(logger.warning(""));
}

TYPED_TEST(LoggerTypedTestFixture, InfoDoesNotRaiseException) { ASSERT_NO_THROW(logger.info("")); }

TYPED_TEST(LoggerTypedTestFixture, DebugDoesNotRaiseException)
{
    ASSERT_NO_THROW(logger.debug(""));
}

TYPED_TEST(LoggerTypedTestFixture, VerboseDoesNotRaiseException)
{
    ASSERT_NO_THROW(logger.verbose(""));
}

TYPED_TEST(LoggerTypedTestFixture, SetLogLevelDoesNotRaiseException)
{
    ASSERT_NO_THROW(logger.setLogLevel(LogLevel::LogLevelInfo));
}

TYPED_TEST(LoggerTypedTestFixture, ClearDoesNotRaiseException) { ASSERT_NO_THROW(logger.clear()); }

/*
TEST(LogTest, GetCompleteLogAfterLog)
{
    Logger l;
    l.debug("bla");

    // TODO Add comparison operator for LogEntry
    ASSERT_EQ(l.getHistory().at(0).message, "bla");
    ASSERT_EQ(l.getHistory().at(0).level, LogLevel::LogLevelDebug);
}
*/
