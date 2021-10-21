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

    Game(std::shared_ptr<RenderWindowInterface> window, float zoom,
        std::shared_ptr<InputManagerInterface> input = nullptr,
        std::shared_ptr<MusicPlayerInterface> musicPlayer = nullptr,
        std::shared_ptr<CamInterface> camera = nullptr);

    void startGame(
        std::shared_ptr<GameState> InitialState, GameLoopFunctionPtr gameloop_function) override;

    void setupRenderTarget() override;

    void setRenderTarget(std::shared_ptr<jt::renderTarget> rt) override;
    std::shared_ptr<jt::renderTarget> getRenderTarget() const override;

    std::shared_ptr<MusicPlayerInterface> getMusicPlayer() override;

    std::shared_ptr<InputManagerInterface> input() override;

    std::shared_ptr<jt::RenderWindowInterface> getRenderWindow() const override;

private:
    std::shared_ptr<jt::renderTarget> m_renderTarget { nullptr };
    std::shared_ptr<jt::RenderWindowInterface> m_window;

    std::shared_ptr<InputManagerInterface> m_input { nullptr };

    jt::Recti m_srcRect;
    jt::Recti m_destRect;

    // override functions from GameBase
    virtual void doUpdate(float const elapsed) override;
    virtual void doDraw() const override;

    std::shared_ptr<MusicPlayerInterface> m_musicPlayer { nullptr };
};

} // namespace jt
#endif
