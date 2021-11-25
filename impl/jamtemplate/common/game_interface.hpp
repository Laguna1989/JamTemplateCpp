#ifndef GUARD_JAMTEMPLATE_GAMEINTERFACE_HPP_GUARD
#define GUARD_JAMTEMPLATE_GAMEINTERFACE_HPP_GUARD

#include "cam_interface.hpp"
#include "input_manager_interface.hpp"
#include "music_player_interface.hpp"
#include "render_target.hpp"
#include "render_window_interface.hpp"
#include "state_manager_interface.hpp"
#include <memory>

namespace jt {

class GameInterface {
public:
    /// Destructor
    virtual ~GameInterface() = default;

    using GameLoopFunctionPtr = std::add_pointer<void()>::type;

    /// Run the Game
    virtual void run() = 0;

    /// Start the game
    /// \param initialState the initial GameState
    /// \param gameloopFunction the game loop function
    virtual void startGame(GameLoopFunctionPtr gameloopFunction) = 0;

    /// Get the render window
    /// \return the render window
    virtual std::shared_ptr<jt::RenderWindowInterface> getRenderWindow() const = 0;

    /// Get the input manager
    /// \return the input manager (can be nullptr)
    virtual std::shared_ptr<InputManagerInterface> input() = 0;

    /// Get the music player
    /// \return the music player (can be nullptr)
    virtual std::shared_ptr<MusicPlayerInterface> getMusicPlayer() = 0;

    /// Get the camera (non const)
    /// \return the camera (can be nullptr)
    virtual std::shared_ptr<CamInterface> getCamera() = 0;

    /// Get the camera (const
    /// \return the camera (can be nullptr)
    virtual std::shared_ptr<CamInterface> getCamera() const = 0;

    /// Get the State Manager
    /// \return the state manager
    virtual std::shared_ptr<StateManagerInterface> getStateManager() = 0;

    /// Set up the render Target
    virtual void setupRenderTarget() = 0;

    /// Get the render Target
    /// \return the render target
    virtual std::shared_ptr<jt::renderTarget> getRenderTarget() const = 0;

protected:
    virtual std::weak_ptr<GameInterface> getPtr() = 0;
};

} // namespace jt

#endif
