#ifndef GUARD_JAMTEMPLATE_MOCK_STATE_MANAGER_HPP
#define GUARD_JAMTEMPLATE_MOCK_STATE_MANAGER_HPP

#include "state_manager/state_manager_interface.hpp"
#include <memory>

class MockStateManager : public ::jt::StateManagerInterface {
public:
    MOCK_METHOD(std::shared_ptr<jt::GameState>, getCurrentState, (), (override));
    MOCK_METHOD(void, switchState, (std::shared_ptr<jt::GameState>), (override));
    MOCK_METHOD(bool, update, (std::weak_ptr<jt::GameInterface>), (override))
    boolupdate(std::weak_ptr<GameInterface> gmock_a0, float elapsed);
};

#endif // GUARD_JAMTEMPLATE_MOCK_STATE_MANAGER_HPP
