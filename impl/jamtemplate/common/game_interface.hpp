#ifndef GUARD_JAMTEMPLATE_GAMEINTERFACE_HPP_GUARD
#define GUARD_JAMTEMPLATE_GAMEINTERFACE_HPP_GUARD

#include "cam_interface.hpp"
#include "game_loop_interface.hpp"
#include "input_manager_interface.hpp"
#include "music_player_interface.hpp"
#include "render_target.hpp"
#include "render_window_interface.hpp"
#include <memory>

namespace jt {

class GameInterface : public GameLoopInterface {
public:
    /// Destructor
    virtual ~GameInterface() = default;

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

    virtual void setupRenderTarget() = 0;
    virtual void setRenderTarget(std::shared_ptr<jt::renderTarget> rt) = 0;
    virtual std::shared_ptr<jt::renderTarget> getRenderTarget() const = 0;

    virtual std::shared_ptr<jt::RenderWindowInterface> getRenderWindow() const = 0;

protected:
    virtual std::weak_ptr<GameInterface> getPtr() = 0;
};

} // namespace jt

#endif
