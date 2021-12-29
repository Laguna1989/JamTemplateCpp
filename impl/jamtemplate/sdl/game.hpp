#ifndef GUARD_JAMTEMPLATE_GAME_HPP_INCLUDEGUARD
#define GUARD_JAMTEMPLATE_GAME_HPP_INCLUDEGUARD

#include "game_base.hpp"
#include "rect.hpp"
#include "render_target.hpp"
#include "render_window_interface.hpp"
#include <chrono>
#include <memory>
#include <string>

namespace jt {

class Game final : public jt::GameBase {
public:
    using Sptr = std::shared_ptr<Game>;

    Game(GfxInterface&, InputManagerInterface& input, MusicPlayerInterface& musicPlayer,
        StateManagerInterface& stateManager, LoggerInterface& logger,
        ActionCommandManagerInterface& actionCommandManager);

    void startGame(GameLoopFunctionPtr gameloop_function) override;

private:
    jt::Recti m_srcRect;
    jt::Recti m_destRect;
    std::shared_ptr<jt::RenderTarget> m_renderTarget { nullptr };

    // override functions from GameBase
    virtual void doUpdate(float const elapsed) override;
    virtual void doDraw() const override;
};

} // namespace jt
#endif
