#ifndef GUARD_JAMTEMPLATE_MOCK_STATE_MANAGER_HPP
#define GUARD_JAMTEMPLATE_MOCK_STATE_MANAGER_HPP

#include "state_manager/state_manager_interface.hpp"
#include <memory>

class MockStateManager : public ::jt::StateManagerInterface {
public:
    MOCK_METHOD(std::shared_ptr<jt::GameState>, getCurrentState, (), (override));
    MOCK_METHOD(void, switchState, (std::shared_ptr<jt::GameState>), (override));
    MOCK_METHOD(void, update, (std::weak_ptr<jt::GameInterface>, float), (override));
    MOCK_METHOD(void, setTransition,
        (std::shared_ptr<jt::StateManagerTransitionInterface> transition), (override));
    MOCK_METHOD(void, draw, (std::shared_ptr<jt::RenderTarget> rt), (override));
};

#endif // GUARD_JAMTEMPLATE_MOCK_STATE_MANAGER_HPP
