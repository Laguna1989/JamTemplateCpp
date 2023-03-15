#ifndef JAMTEMPLATE_MOCK_STATE_MANAGER_HPP
#define JAMTEMPLATE_MOCK_STATE_MANAGER_HPP

#include <state_manager/state_manager_interface.hpp>
#include <memory>

class MockStateManager : public ::jt::StateManagerInterface {
public:
    MOCK_METHOD(std::shared_ptr<jt::GameState>, getCurrentState, (), (override));
    MOCK_METHOD(void, switchState, (std::shared_ptr<jt::GameState>), (override));
    MOCK_METHOD(void, update, (std::weak_ptr<jt::GameInterface>, float), (override));
    MOCK_METHOD(void, setTransition,
        (std::shared_ptr<jt::StateManagerTransitionInterface> transition), (override));
    MOCK_METHOD(
        std::shared_ptr<jt::StateManagerTransitionInterface>, getTransition, (), (override));
    MOCK_METHOD(void, draw, (std::shared_ptr<jt::RenderTargetInterface> rt), (override));
    MOCK_METHOD(void, switchToStoredState, (std::string const&), (override));
    MOCK_METHOD(void, storeCurrentState, (std::string const&), (override));
    MOCK_METHOD(std::shared_ptr<jt::GameState>, getStoredState, (std::string const&), (override));
    MOCK_METHOD(void, clearStoredState, (std::string const&), (override));
    MOCK_METHOD(std::vector<std::string>, getStoredStateIdentifiers, (), (const, override));
};

#endif // JAMTEMPLATE_MOCK_STATE_MANAGER_HPP
