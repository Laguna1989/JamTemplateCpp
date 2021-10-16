#ifndef GUARD_JAMTEMPLATE_GAMELOOPINTERFACE_HPP_GUARD
#define GUARD_JAMTEMPLATE_GAMELOOPINTERFACE_HPP_GUARD

#include "game_state.hpp"
#include <type_traits>

namespace jt {

class GameLoopInterface {
public:
    using GameLoopFunctionPtr = std::add_pointer<void()>::type;

    // this function will likely be called by the user from within update().
    // To ensure consisten behavior within one frame, the actual switching will take place in
    // doSwitchState() which will happen at the beginning of the next update loop.
    virtual void switchState(std::shared_ptr<GameState> newState) = 0;

    virtual std::shared_ptr<GameState> getCurrentState() = 0;

    virtual void run() = 0;
    virtual void startGame(
        std::shared_ptr<GameState> InitialState, GameLoopFunctionPtr gameloop_function)
        = 0;
};
} // namespace jt
#endif
