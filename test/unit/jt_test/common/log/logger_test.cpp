#include <log/logger.hpp>
#include <log/logger_null.hpp>
#include <mocks/mock_history.hpp>
#include <mocks/mock_log_target.hpp>
#include <gtest/gtest.h>

template <typename T>
class LoggerTypedTestFixture : public ::testing::Test { };

using MyTypes = testing::Types<jt::Logger, jt::null_objects::LoggerNull>;
TYPED_TEST_SUITE(LoggerTypedTestFixture, MyTypes);

TYPED_TEST(LoggerTypedTestFixture, AddNullptrLogTarget)
{
    TypeParam logger;
    ASSERT_NO_THROW(logger.addLogTarget(nullptr));
}

TYPED_TEST(LoggerTypedTestFixture, AddMockLogTarget)
{
    TypeParam logger;
    ASSERT_NO_THROW(logger.addLogTarget(std::make_shared<MockLogTarget>()));
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
    ASSERT_NO_THROW(logger.setLogLevel(jt::LogLevel::Info));
}

TEST(LoggerTest, LogToMockTargetForwardsToTarget)
{
    jt::Logger logger {};
    auto target = std::make_shared<MockLogTarget>();
    logger.addLogTarget(target);
    EXPECT_CALL(*target, log(::testing::_));
    logger.fatal("", {});
}
