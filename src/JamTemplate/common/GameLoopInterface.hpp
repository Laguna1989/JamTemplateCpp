#ifndef GUARD_JAMTEMPLATE_GAMELOOPINTERFACE_HPP_GUARD
#define GUARD_JAMTEMPLATE_GAMELOOPINTERFACE_HPP_GUARD

#include "GameState.hpp"

namespace jt {

class GameLoopInterface {
public:
    // Ugly c-style function Pointer required by emscripten. At least it is hidden in a using alias.
    using GameLoopFunctionPtr = void (*)();

    // this function will likely be called by the user from within update().
    // To ensure consisten behavior within one frame, the actual switching will take place in
    // doSwitchState() which will happen at the beginning of the next update loop.
    virtual void switchState(std::shared_ptr<GameState> newState) = 0;

    virtual std::shared_ptr<GameState> getCurrentSate() = 0;

    virtual void run() = 0;
    virtual void startGame(
        std::shared_ptr<GameState> InitialState, GameLoopFunctionPtr gameloop_function)
        = 0;
};
} // namespace jt
#endif
