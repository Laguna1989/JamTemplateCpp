#include "mocks/mock_input.hpp"
#include "state_manager/state_manager_transition_none.hpp"
#include <backend_setup.hpp>
#include <mocks/mock_game.hpp>
#include <mocks/mock_state.hpp>
#include <state_manager/state_manager.hpp>
#include <gtest/gtest.h>

TEST(StateManagerTest, InitialCurrentStateIsNullptr)
{
    auto initialState = std::make_shared<MockState>();
    jt::StateManager stateManager { initialState };

    ASSERT_EQ(stateManager.getCurrentState(), nullptr);
}

TEST(StateManagerTest, InitialNextStateReturnsCorrectImpl)
{
    auto initialState = std::make_shared<MockState>();
    jt::StateManager stateManager { initialState };

    ASSERT_EQ(initialState, stateManager.getNextState());
}

TEST(StateManagerTest, CheckForGameStateSwitchReturnsTrue)
{
    jt::StateManager stateManager { std::make_shared<::testing::NiceMock<MockState>>() };

    auto const game = std::make_shared<::testing::NiceMock<MockGame>>();
    // Note: Throw because of window being a default constructed object.
    ASSERT_ANY_THROW(stateManager.update(game, 0.0f));
}

TEST(StateManagerTest, SwitchToNullptrStateThrows)
{
    jt::StateManager stateManager { std::make_shared<MockState>() };
    ASSERT_THROW(stateManager.switchState(nullptr), std::invalid_argument);
}

TEST(StateManagerTest, SwitchToValidState)
{
    jt::StateManager stateManager { std::make_shared<MockState>() };
    auto otherState = std::make_shared<MockState>();
    ASSERT_NO_THROW(stateManager.switchState(otherState));
}

TEST(StateManagerTest, SetGetTransition)
{
    jt::StateManager stateManager { std::make_shared<MockState>() };
    auto transition = std::make_shared<jt::StateManagerTransitionNone>();
    stateManager.setTransition(transition);
    ASSERT_EQ(stateManager.getTransition(), transition);
}

TEST(StateManagerTest, getStoredStateIdentifiersIsInitiallyEmpty)
{
    jt::StateManager stateManager { std::make_shared<MockState>() };
    ASSERT_TRUE(stateManager.getStoredStateIdentifiers().empty());
}

TEST(StateManagerTest, getStoredStateIdentifiersAfterStoreState)
{
    jt::StateManager stateManager { std::make_shared<MockState>() };

    stateManager.storeCurrentState("testState");
    auto const stateIdentifiers = stateManager.getStoredStateIdentifiers();
    ASSERT_FALSE(stateIdentifiers.empty());
    ASSERT_EQ(stateIdentifiers.size(), 1u);
    ASSERT_EQ(stateIdentifiers.at(0), "testState");
}

TEST(StateManagerTest, getStoredStateIdentifiersAfterClear)
{
    jt::StateManager stateManager { std::make_shared<MockState>() };

    stateManager.storeCurrentState("testState");
    stateManager.clearStoredState("testState");
    ASSERT_TRUE(stateManager.getStoredStateIdentifiers().empty());
}

TEST(StateManagerTest, getStoredStateReturnsNullptrByDefault)
{
    jt::StateManager stateManager { std::make_shared<MockState>() };
    ASSERT_EQ(stateManager.getStoredState("abcd"), nullptr);
}

TEST(StateManagerTest, getStoredStateReturnsValidPointer)
{
    jt::StateManager stateManager { std::make_shared<::testing::NiceMock<MockState>>() };
    auto game = std::make_shared<::testing::NiceMock<MockGame>>();
    ::testing::NiceMock<MockInput> input;
    ON_CALL(*game, input()).WillByDefault(::testing::ReturnRef(input));
    stateManager.update(game, 0.1f);
    stateManager.storeCurrentState("test state");
    ASSERT_NE(stateManager.getStoredState("test state"), nullptr);
}

TEST(StateManagerTest, UpdateAndDraw)
{
    jt::StateManager stateManager { std::make_shared<::testing::NiceMock<MockState>>() };
    auto game = std::make_shared<::testing::NiceMock<MockGame>>();
    ::testing::NiceMock<MockInput> input;
    ON_CALL(*game, input()).WillByDefault(::testing::ReturnRef(input));
    stateManager.update(game, 0.1f);
    ASSERT_NO_THROW(stateManager.draw(game->gfx().target()));
}

class MockTransition : public jt::StateManagerTransitionInterface {
public:
    MOCK_METHOD(void, start, (), (override));
    MOCK_METHOD(bool, isInProgress, (), (override));
    MOCK_METHOD(bool, triggerStateChange, (), (override));
    MOCK_METHOD(void, update, (float elapsed), (override));
    MOCK_METHOD(void, draw, (std::shared_ptr<jt::RenderTargetInterface>), (override));
};

TEST(StateManagerTest, UpdateAndDrawWithTransition)
{
    jt::StateManager stateManager { std::make_shared<::testing::NiceMock<MockState>>() };
    auto const transition = std::make_shared<MockTransition>();
    stateManager.setTransition(transition);

    auto game = std::make_shared<::testing::NiceMock<MockGame>>();

    ::testing::NiceMock<MockInput> input;
    ON_CALL(*game, input()).WillByDefault(::testing::ReturnRef(input));
    EXPECT_CALL(*transition, update(::testing::_));
    EXPECT_CALL(*transition, triggerStateChange).WillOnce(::testing::Return(true));
    EXPECT_CALL(*transition, isInProgress).WillOnce(::testing::Return(true));
    EXPECT_CALL(*transition, draw(::testing::_));
    stateManager.update(game, 0.1f);
    ASSERT_NO_THROW(stateManager.draw(game->gfx().target()));
}

TEST(StateManagerTest, switchToStoredStateWithInvalidState)
{
    auto const firstState = std::make_shared<::testing::NiceMock<MockState>>();

    jt::StateManager stateManager { firstState };
    ASSERT_THROW(stateManager.switchToStoredState("non existing"), std::invalid_argument);
}

TEST(StateManagerTest, switchToStoredState)
{
    auto const firstState = std::make_shared<::testing::NiceMock<MockState>>();
    auto const secondState = std::make_shared<::testing::NiceMock<MockState>>();

    jt::StateManager stateManager { firstState };
    auto game = std::make_shared<::testing::NiceMock<MockGame>>();
    ::testing::NiceMock<MockInput> input;
    ON_CALL(*game, input()).WillByDefault(::testing::ReturnRef(input));
    stateManager.update(game, 0.1f);
    stateManager.storeCurrentState("first state");
    stateManager.switchState(secondState);
    stateManager.update(game, 0.1f);

    stateManager.switchToStoredState("first state");
    stateManager.update(game, 0.1f);

    ASSERT_EQ(stateManager.getCurrentState(), firstState);
}
