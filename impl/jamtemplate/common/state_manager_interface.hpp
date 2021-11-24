#ifndef MYAWESOMEGAME_STATE_MANAGER_INTERFACE_HPP
#define MYAWESOMEGAME_STATE_MANAGER_INTERFACE_HPP

namespace jt {

class StateManagerInterface {
public:
    virtual ~StateManagerInterface() = default;
    virtual std::shared_ptr<GameState> getCurrentState() = 0;
    virtual void switchState(std::shared_ptr<GameState> newState) = 0;
    virtual void doSwitchState(std::weak_ptr<GameInterface> gameInstace) = 0;
    virtual bool checkForGameStateSwitch(std::weak_ptr<GameInterface> gameInstace) = 0;
};
} // namespace jt

#endif // MYAWESOMEGAME_STATE_MANAGER_INTERFACE_HPP
