#include <box2dwrapper/box2d_contact_manager.hpp>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

TEST(Box2DContactManagerTest, InitiallyZeroCallbacksRegistered)
{
    jt::Box2DContactManager manager;
    ASSERT_EQ(manager.size(), 0u);
}

TEST(Box2DContactManagerTest, RegisterIncreasesSizeIfNew)
{
    jt::Box2DContactManager manager;
    manager.registerCallback("empty_callback1", nullptr);
    ASSERT_EQ(manager.size(), 1u);
    manager.registerCallback("empty_callback2", nullptr);
    ASSERT_EQ(manager.size(), 2u);
}

TEST(Box2DContactManagerTest, RegisterDoesNotIncreaseSizeIfAlreadyKnown)
{
    jt::Box2DContactManager manager;
    manager.registerCallback("callback_to_override", nullptr);
    ASSERT_EQ(manager.size(), 1u);
    manager.registerCallback("callback_to_override", nullptr);
    ASSERT_EQ(manager.size(), 1u);
}

TEST(Box2DContactManagerTest, UnregisterDecreasesSize)
{
    jt::Box2DContactManager manager;
    manager.registerCallback("empty_callback1", nullptr);
    manager.registerCallback("empty_callback2", nullptr);
    // sanity check
    ASSERT_EQ(manager.size(), 2u);
    manager.unregisterCallback("empty_callback1");
    ASSERT_EQ(manager.size(), 1u);
    manager.unregisterCallback("empty_callback2");
    ASSERT_EQ(manager.size(), 0u);
}

TEST(Box2DContactManagerTest, UnregisterOfNonExistingCallbackHasNoEffect)
{
    jt::Box2DContactManager manager;
    manager.registerCallback("empty_callback1", nullptr);

    ASSERT_NO_THROW(manager.unregisterCallback("empty_callback2"));
}

TEST(Box2DContactManagerTest, ListOfIdentifiersIsCorrect)
{
    jt::Box2DContactManager manager;
    manager.registerCallback("A", nullptr);
    manager.registerCallback("B", nullptr);
    manager.registerCallback("C", nullptr);
    manager.registerCallback("D", nullptr);
    auto const identifiers = manager.getAllCallbackIdentifiers();
    ASSERT_THAT(identifiers, ::testing::ElementsAre("A", "B", "C", "D"));
}

class MockContactCallback : public jt::Box2DContactCallbackInterface {
public:
    MOCK_METHOD(void, onBeginContact, (b2Contact*), (override));
    MOCK_METHOD(void, onEndContact, (b2Contact*), (override));

    MOCK_METHOD(void, setEnabled, (bool), (override));
    MOCK_METHOD(bool, getEnabled, (), (const, override));
    MockContactCallback() { ON_CALL(*this, getEnabled).WillByDefault(::testing::Return(true)); }
};

TEST(Box2DContactManagerTest, CallsRegisteredCallbackBegin)
{
    jt::Box2DContactManager manager;
    auto callback = std::make_shared<::testing::NiceMock<MockContactCallback>>();
    manager.registerCallback("mock_callback", callback);

    EXPECT_CALL(*callback, onBeginContact(nullptr));
    manager.BeginContact(nullptr);
}

TEST(Box2DContactManagerTest, CallsRegisteredCallbackEnd)
{
    jt::Box2DContactManager manager;
    auto callback = std::make_shared<::testing::NiceMock<MockContactCallback>>();
    manager.registerCallback("mock_callback", callback);

    EXPECT_CALL(*callback, onEndContact(nullptr));
    manager.EndContact(nullptr);
}

TEST(Box2DContactManagerTest, CallbacksAreNotInvokedForDisabledCallback)
{
    jt::Box2DContactManager manager;
    auto callback = std::make_shared<::testing::NiceMock<MockContactCallback>>();
    manager.registerCallback("mock_callback", callback);

    ON_CALL(*callback, getEnabled).WillByDefault(::testing::Return(false));

    EXPECT_CALL(*callback, onBeginContact(::testing::_)).Times(0);
    EXPECT_CALL(*callback, onEndContact(::testing::_)).Times(0);
    manager.BeginContact(nullptr);
    manager.EndContact(nullptr);
}
