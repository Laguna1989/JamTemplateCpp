#ifndef GUARD_JAMTEMPLATE_GAMEINTERFACE_HPP_GUARD
#define GUARD_JAMTEMPLATE_GAMEINTERFACE_HPP_GUARD

#include "action_commands/action_command_manager_interface.hpp"
#include "audio/audio_interface.hpp"
#include "cam_interface.hpp"
#include "gfx_interface.hpp"
#include "input/input_manager_interface.hpp"
#include "logging/logger_interface.hpp"
#include "render_target.hpp"
#include "render_window_interface.hpp"
#include "state_manager/state_manager_interface.hpp"
#include <memory>

namespace jt {

class GameInterface {
public:
    /// Destructor
    virtual ~GameInterface() = default;

    using GameLoopFunctionPtr = std::add_pointer<void()>::type;

    /// Run one frame of the Game
    virtual void runOneFrame() = 0;

    /// Start the game
    /// \param initialState the initial GameState
    /// \param gameloopFunction the game loop function
    virtual void startGame(GameLoopFunctionPtr gameloopFunction) = 0;

    /// Get the graphics context
    /// \return the graphics context
    virtual GfxInterface& gfx() const = 0;

    /// Get the input manager
    /// \return the input manager
    virtual InputManagerInterface& input() = 0;

    /// Get the music player
    /// \return the music player
    virtual AudioInterface& audio() = 0;

    /// Get the State Manager
    /// \return the state manager
    virtual StateManagerInterface& getStateManager() = 0;

    /// Get the logger
    /// \return the logger
    virtual LoggerInterface& getLogger() = 0;

    /// Get the ActionCommandManager
    /// \return the action command manager
    virtual ActionCommandManagerInterface& getActionCommandManager() = 0;

    /// Reset the Game internals, i.e. on a state switch
    virtual void reset() = 0;

protected:
    virtual std::weak_ptr<GameInterface> getPtr() = 0;
};

} // namespace jt

#endif
