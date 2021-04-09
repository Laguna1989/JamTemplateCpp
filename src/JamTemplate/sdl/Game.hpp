#ifndef GUARD_JAMTEMPLATE_GAME_HPP_INCLUDEGUARD
#define GUARD_JAMTEMPLATE_GAME_HPP_INCLUDEGUARD

#include "GameBase.hpp"
#include "Rect.hpp"
#include "Rendertarget.hpp"
#include <chrono>
#include <memory>
#include <string>

namespace jt {

class Game final : public jt::GameBase {
public:
    using Sptr = std::shared_ptr<Game>;

    Game(unsigned int w, unsigned int h, float zoom, std::string const& title,
        std::shared_ptr<MusicPlayerInterface> musicPlayer);

    void setRenderTarget(std::shared_ptr<jt::renderTarget> rt) override;
    std::shared_ptr<jt::renderTarget> getRenderTarget() const override;

    void runGame(
        std::shared_ptr<GameState> InitialState, GameLoopFunctionPtr gameloop_function) override;

    virtual std::shared_ptr<MusicPlayerInterface> getMusicPlayer() override;

private:
    std::shared_ptr<jt::renderTarget> m_renderTarget { nullptr };
    std::shared_ptr<SDL_Window> m_window;

    jt::Recti m_srcRect;
    jt::Recti m_destRect;
    jt::Vector2 m_fullsize;

    // override functions from GameBase
    virtual void doUpdate(float const elapsed) override;
    virtual void doDraw() const override;

    void updateShake(float elapsed) override;

    std::shared_ptr<MusicPlayerInterface> m_musicPlayer { nullptr };
};

} // namespace jt
#endif
