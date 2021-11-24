#ifndef GUARD_JAMTEMPLATE_MOCK_STATE_MANAGER_HPP
#define GUARD_JAMTEMPLATE_MOCK_STATE_MANAGER_HPP

#include "state_manager_interface.hpp"
#include <memory>

class MockStateManager : public ::jt::StateManagerInterface {
public:
    MOCK_METHOD(std::shared_ptr<jt::GameState>, getCurrentState, (), (override));
    MOCK_METHOD(void, switchState, (std::shared_ptr<jt::GameState> newState), (override));
    MOCK_METHOD(void, doSwitchState, (std::weak_ptr<jt::GameInterface> gameInstace), (override));
    MOCK_METHOD(
        bool, checkForGameStateSwitch, (std::weak_ptr<jt::GameInterface> gameInstace), (override));
};

#endif // GUARD_JAMTEMPLATE_MOCK_STATE_MANAGER_HPP
