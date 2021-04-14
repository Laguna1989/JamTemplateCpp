#ifndef GUARD_JAMTEMPLATE_GAME_HPP_INCLUDEGUARD
#define GUARD_JAMTEMPLATE_GAME_HPP_INCLUDEGUARD

#include "GameBase.hpp"
#include "Rendertarget.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <memory>
#include <string>

namespace jt {

//
// Game class to be implemented by sfml/sdl
//
class Game final : public jt::GameBase {
public:
    using Sptr = std::shared_ptr<Game>;

    Game(unsigned int w, unsigned int h, float zoom, std::string const& title,
        std::shared_ptr<MusicPlayerInterface> musicPlayer = nullptr);

    void startGame(
        std::shared_ptr<GameState> InitialState, GameLoopFunctionPtr gameloop_function) override;

    void setRenderTarget(std::shared_ptr<jt::renderTarget> rt) override;
    std::shared_ptr<jt::renderTarget> getRenderTarget() const override;

    virtual std::shared_ptr<MusicPlayerInterface> getMusicPlayer() override;

private:
    std::shared_ptr<jt::renderTarget> m_renderTarget { nullptr };
    std::shared_ptr<sf::View> m_view { nullptr };
    std::shared_ptr<sf::RenderWindow> m_renderWindow { nullptr };

    std::shared_ptr<MusicPlayerInterface> m_musicPlayer { nullptr };

    // override functions from GameBase
    virtual void doUpdate(float const elapsed) override;
    virtual void doDraw() const override;

    void updateShake(float elapsed) override;
    void applyCamShakeToView();
    void removeCamShakeFromView();

    void setView(std::shared_ptr<sf::View> view);
    std::shared_ptr<sf::View> getView();

    std::shared_ptr<sf::RenderWindow> getRenderWindow();
};

} // namespace jt
#endif
