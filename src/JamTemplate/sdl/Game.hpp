#ifndef JAMTEMPLATE_GAME_HPP_INCLUDEGUARD
#define JAMTEMPLATE_GAME_HPP_INCLUDEGUARD

#include "GameBase.hpp"
#include "rect.hpp"
#include "rendertarget.hpp"
#include <chrono>
#include <memory>
#include <string>

namespace JamTemplate {

//
// Game class to be implemented by sfml/sdl
//
class Game final : public JamTemplate::GameBase {
public:
    using Sptr = std::shared_ptr<Game>;

    Game(unsigned int w, unsigned int h, float zoom, std::string const& title);

    void setRenderTarget(std::shared_ptr<jt::renderTarget> rt) override;
    std::shared_ptr<jt::renderTarget> getRenderTarget() const override;

    void runGame(std::shared_ptr<GameState> InitialState) override;
    void run();

private:
    std::shared_ptr<jt::renderTarget> m_renderTarget { nullptr };
    std::shared_ptr<SDL_Window> m_window;
    std::shared_ptr<SDL_Surface> m_surface;

    jt::recti m_srcRect;
    jt::vector2 m_fullsize;

    // override functions from GameBase
    virtual void doUpdate(float const elapsed) override;
    virtual void doDraw() const override;

    void updateShake(float elapsed) override;
    void resetShake() override;
};

} // namespace JamTemplate
#endif
