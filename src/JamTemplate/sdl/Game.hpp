#ifndef GUARD_JAMTEMPLATE_GAME_HPP_INCLUDEGUARD
#define GUARD_JAMTEMPLATE_GAME_HPP_INCLUDEGUARD

#include "GameBase.hpp"
#include "Rect.hpp"
#include "RenderWindowInterface.hpp"
#include "Rendertarget.hpp"
#include <chrono>
#include <memory>
#include <string>

namespace jt {

class Game final : public jt::GameBase {
public:
    using Sptr = std::shared_ptr<Game>;

    Game(std::shared_ptr<RenderWindowInterface> window, float zoom,
        std::shared_ptr<MusicPlayerInterface> musicPlayer = nullptr);

    void setRenderTarget(std::shared_ptr<jt::renderTarget> rt) override;
    std::shared_ptr<jt::renderTarget> getRenderTarget() const override;

    virtual void setupRenderTarget() override;

    void startGame(
        std::shared_ptr<GameState> InitialState, GameLoopFunctionPtr gameloop_function) override;

    virtual std::shared_ptr<MusicPlayerInterface> getMusicPlayer() override;

private:
    std::shared_ptr<jt::renderTarget> m_renderTarget { nullptr };
    std::shared_ptr<jt::RenderWindowInterface> m_window;

    jt::Recti m_srcRect;
    jt::Recti m_destRect;

    // override functions from GameBase
    virtual void doUpdate(float const elapsed) override;
    virtual void doDraw() const override;

    void updateShake(float elapsed) override;

    std::shared_ptr<MusicPlayerInterface> m_musicPlayer { nullptr };
};

} // namespace jt
#endif
