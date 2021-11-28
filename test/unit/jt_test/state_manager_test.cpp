#include "mocks/mock_game.hpp"
#include "mocks/mock_state.hpp"
#include "state_manager.hpp"
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

TEST(StateManagerTest, CurrentStateCorrectAfterCheckForGameStateSwitch)
{
    auto initialState = std::make_shared<MockState>();
    jt::StateManager stateManager { initialState };

    auto game = std::make_shared<MockGame>();
    stateManager.checkAndPerformSwitchState(game);

    ASSERT_EQ(initialState, stateManager.getCurrentState());
}

TEST(StateManagerTest, NextStateCorrectAfterCheckForGameStateSwitch)
{
    auto initialState = std::make_shared<MockState>();
    jt::StateManager stateManager { initialState };

    auto game = std::make_shared<MockGame>();
    stateManager.checkAndPerformSwitchState(game);

    ASSERT_EQ(nullptr, stateManager.getNextState());
}

TEST(StateManagerTest, CheckForGameStateSwitchReturnsTrue)
{
    auto initialState = std::make_shared<MockState>();
    jt::StateManager stateManager { initialState };

    auto game = std::make_shared<MockGame>();
    ASSERT_TRUE(stateManager.checkAndPerformSwitchState(game));
}

TEST(StateManagerTest, CheckForGameStateSwitchReturnsFalseWhenCalledASecondTime)
{
    auto initialState = std::make_shared<MockState>();
    jt::StateManager stateManager { initialState };

    auto game = std::make_shared<MockGame>();
    stateManager.checkAndPerformSwitchState(game);
    ASSERT_FALSE(stateManager.checkAndPerformSwitchState(game));
}

TEST(StateManagerTest, SwitchToNullptrStateThrows)
{
    jt::StateManager stateManager { std::make_shared<MockState>() };
    ASSERT_THROW(stateManager.switchState(nullptr), std::invalid_argument);
}
