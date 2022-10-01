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
    auto initialState = std::make_shared<MockState>();
    jt::StateManager stateManager { initialState };

    auto game = std::make_shared<MockGame>();
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
