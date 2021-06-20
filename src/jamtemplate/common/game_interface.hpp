#ifndef GUARD_JAMTEMPLATE_GAMEINTERFACE_HPP_GUARD
#define GUARD_JAMTEMPLATE_GAMEINTERFACE_HPP_GUARD

#include "cam_interface.hpp"
#include "game_loop_interface.hpp"
#include "input_manager_interface.hpp"
#include "music_player_interface.hpp"
#include "render_target.hpp"
#include <memory>

namespace jt {
class GameState;

class GameInterface : public GameLoopInterface {
public:
    virtual std::shared_ptr<InputManagerInterface> input() = 0;

    virtual std::shared_ptr<MusicPlayerInterface> getMusicPlayer() = 0;

    virtual std::shared_ptr<CamInterface> getCamera() = 0;
    virtual std::shared_ptr<CamInterface> getCamera() const = 0;

    virtual void setupRenderTarget() = 0;
    virtual void setRenderTarget(std::shared_ptr<jt::renderTarget> rt) = 0;
    virtual std::shared_ptr<jt::renderTarget> getRenderTarget() const = 0;

protected:
    virtual std::weak_ptr<GameInterface> getPtr() = 0;
};

} // namespace jt

#endif
