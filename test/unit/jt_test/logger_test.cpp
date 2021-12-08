#include "logging/logger.hpp"
#include "logging/logger_null.hpp"
#include <gtest/gtest.h>

template <typename T>
class LoggerTypedTestFixture : public ::testing::Test {
};

using MyTypes = testing::Types<jt::Logger, jt::null_objects::LoggerNull>;
TYPED_TEST_SUITE(LoggerTypedTestFixture, MyTypes);

TYPED_TEST(LoggerTypedTestFixture, GetCompleteLogIsEmptyByDefault)
{
    TypeParam logger;
    ASSERT_TRUE(logger.getHistory().empty());
}

TYPED_TEST(LoggerTypedTestFixture, AddNullptrLogTarget)
{
    TypeParam logger;
    ASSERT_NO_THROW(logger.addLogTarget(nullptr));
}

TYPED_TEST(LoggerTypedTestFixture, ActionDoesNotRaiseException)
{
    TypeParam logger;
    ASSERT_NO_THROW(logger.action(""));
}

TYPED_TEST(LoggerTypedTestFixture, FatalDoesNotRaiseException)
{
    TypeParam logger;
    ASSERT_NO_THROW(logger.fatal(""));
}

TYPED_TEST(LoggerTypedTestFixture, ErrorDoesNotRaiseException)
{
    TypeParam logger;
    ASSERT_NO_THROW(logger.error(""));
}

TYPED_TEST(LoggerTypedTestFixture, WarnDoesNotRaiseException)
{
    TypeParam logger;
    ASSERT_NO_THROW(logger.warning(""));
}

TYPED_TEST(LoggerTypedTestFixture, InfoDoesNotRaiseException)
{
    TypeParam logger;
    ASSERT_NO_THROW(logger.info(""));
}

TYPED_TEST(LoggerTypedTestFixture, DebugDoesNotRaiseException)
{
    TypeParam logger;
    ASSERT_NO_THROW(logger.debug(""));
}

TYPED_TEST(LoggerTypedTestFixture, VerboseDoesNotRaiseException)
{
    TypeParam logger;
    ASSERT_NO_THROW(logger.verbose(""));
}

TYPED_TEST(LoggerTypedTestFixture, SetLogLevelDoesNotRaiseException)
{
    TypeParam logger;
    ASSERT_NO_THROW(logger.setLogLevel(LogLevel::LogLevelInfo));
}

TYPED_TEST(LoggerTypedTestFixture, ClearDoesNotRaiseException)
{
    TypeParam logger;
    ASSERT_NO_THROW(logger.clear());
}
