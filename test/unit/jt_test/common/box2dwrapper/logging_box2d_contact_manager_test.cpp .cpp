#include <box2dwrapper/logging_box2d_contact_manager.hpp>
#include <mocks/mock_logger.hpp>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <stdexcept>

TEST(LoggingBox2DContactManagerTest, ConstructorWithNullptrThrowsException)
{
    ::testing::NiceMock<MockLogger> logger;
    auto const func = [&logger]() { jt::LoggingBox2DContactManager { nullptr, logger }; };
    ASSERT_THROW(func(), std::invalid_argument);
}

TEST(LoggingBox2DContactManagerTest, ConstructorWithNullptrLogsFatal)
{
    MockLogger logger;
    EXPECT_CALL(logger, fatal(::testing::_, ::testing::_));
    auto const func = [&logger]() { jt::LoggingBox2DContactManager { nullptr, logger }; };
    ASSERT_THROW(func(), std::invalid_argument);
}

class MockBox2DContactManager : public jt::Box2DContactManagerInterface {
public:
    MOCK_METHOD(std::size_t, size, (), (const, override));
    MOCK_METHOD(void, registerCallback,
        (std::string const&, std::shared_ptr<jt::Box2DContactCallbackInterface>), (override));
    MOCK_METHOD(void, unregisterCallback, (std::string const&), (override));
    MOCK_METHOD(std::vector<std::string>, getAllCallbackIdentifiers, (), (const, override));
    MOCK_METHOD(void, BeginContact, (b2Contact*), (override));
    MOCK_METHOD(void, EndContact, (b2Contact*), (override));
};

TEST(LoggingBox2DContactManagerTest, ConstructorLogsInfo)
{
    MockLogger logger;
    auto decoratee = std::make_shared<MockBox2DContactManager>();
    EXPECT_CALL(logger, info(::testing::_, ::testing::_));
    jt::LoggingBox2DContactManager { decoratee, logger };
}

TEST(LoggingBox2DContactManagerTest, SizeLogsVerbose)
{
    ::testing::NiceMock<MockLogger> logger;
    auto decoratee = std::make_shared<MockBox2DContactManager>();
    auto contactManager = jt::LoggingBox2DContactManager { decoratee, logger };
    EXPECT_CALL(*decoratee, size());
    EXPECT_CALL(logger, verbose(::testing::_, ::testing::_));
    contactManager.size();
}

TEST(LoggingBox2DContactManagerTest, RegisterCallbackLogsInfo)
{
    ::testing::NiceMock<MockLogger> logger;
    auto decoratee = std::make_shared<MockBox2DContactManager>();
    auto contactManager = jt::LoggingBox2DContactManager { decoratee, logger };
    EXPECT_CALL(*decoratee, registerCallback("abcd", ::testing::_));
    EXPECT_CALL(logger, info(::testing::_, ::testing::_));
    contactManager.registerCallback("abcd", nullptr);
}

TEST(LoggingBox2DContactManagerTest, UnregisterCallbackLogsInfo)
{
    ::testing::NiceMock<MockLogger> logger;
    auto decoratee = std::make_shared<MockBox2DContactManager>();
    auto contactManager = jt::LoggingBox2DContactManager { decoratee, logger };
    EXPECT_CALL(*decoratee, unregisterCallback(::testing::_));
    EXPECT_CALL(logger, info(::testing::_, ::testing::_));
    contactManager.unregisterCallback("abcd");
}

TEST(LoggingBox2DContactManagerTest, GetAllCallbackIdentifiersLogsVerbose)
{
    ::testing::NiceMock<MockLogger> logger;
    auto decoratee = std::make_shared<MockBox2DContactManager>();
    auto contactManager = jt::LoggingBox2DContactManager { decoratee, logger };
    EXPECT_CALL(*decoratee, getAllCallbackIdentifiers());
    EXPECT_CALL(logger, verbose(::testing::_, ::testing::_));
    contactManager.getAllCallbackIdentifiers();
}

TEST(LoggingBox2DContactManagerTest, BeginContactLogsDebug)
{
    ::testing::NiceMock<MockLogger> logger;
    auto decoratee = std::make_shared<MockBox2DContactManager>();
    auto contactManager = jt::LoggingBox2DContactManager { decoratee, logger };
    EXPECT_CALL(*decoratee, BeginContact(::testing::_));
    EXPECT_CALL(logger, debug(::testing::_, ::testing::_));
    contactManager.BeginContact(nullptr);
}

TEST(LoggingBox2DContactManagerTest, EndContactLogsDebug)
{
    ::testing::NiceMock<MockLogger> logger;
    auto decoratee = std::make_shared<MockBox2DContactManager>();
    auto contactManager = jt::LoggingBox2DContactManager { decoratee, logger };
    EXPECT_CALL(*decoratee, EndContact(::testing::_));
    EXPECT_CALL(logger, debug(::testing::_, ::testing::_));
    contactManager.EndContact(nullptr);
}
