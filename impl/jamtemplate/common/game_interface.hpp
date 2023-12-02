#ifndef JAMTEMPLATE_GAMEINTERFACE_HPP
#define JAMTEMPLATE_GAMEINTERFACE_HPP

#include <action_commands/action_command_manager_interface.hpp>
#include <audio/audio/audio_interface.hpp>
#include <cache/cache_interface.hpp>
#include <graphics/gfx_interface.hpp>
#include <input/input_manager_interface.hpp>
#include <log/logger_interface.hpp>
#include <state_manager/state_manager_interface.hpp>
#include <memory>

namespace jt {

class GameInterface {
public:
    /// Get the graphics context
    /// \return the graphics context
    virtual GfxInterface& gfx() const = 0;

    /// Get the input manager
    /// \return the input manager
    virtual InputGetInterface& input() = 0;

    /// Get the music player
    /// \return the music player
    virtual AudioInterface& audio() = 0;

    /// Get the State Manager
    /// \return the state manager
    virtual StateManagerInterface& stateManager() = 0;

    /// Get the logger
    /// \return the logger
    virtual LoggerInterface& logger() = 0;

    /// Get the ActionCommandManager
    /// \return the action command manager
    virtual ActionCommandManagerInterface& actionCommandManager() = 0;

    /// Get the cache
    /// \return the cache
    virtual CacheInterface& cache() = 0;

    /// Reset the Game internals, i.e. on a state switch
    virtual void reset() = 0;

    /// Destructor
    virtual ~GameInterface() = default;

    // no copy, no move. Avoid slicing.
    GameInterface(GameInterface const&) = delete;
    GameInterface(GameInterface&&) = delete;
    GameInterface& operator=(GameInterface const&) = delete;
    GameInterface& operator=(GameInterface&&) = delete;

protected:
    // default constructor can only be called from derived classes
    GameInterface() = default;
    virtual std::weak_ptr<GameInterface> getPtr() = 0;
};

} // namespace jt

#endif
