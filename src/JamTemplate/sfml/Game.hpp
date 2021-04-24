#ifndef GUARD_JAMTEMPLATE_GAME_HPP_INCLUDEGUARD
#define GUARD_JAMTEMPLATE_GAME_HPP_INCLUDEGUARD

#include "GameBase.hpp"
#include "RenderWindowInterface.hpp"
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

    Game(std::shared_ptr<RenderWindowInterface> window, float zoom,
        std::shared_ptr<InputManagerInterface> inputManager = nullptr,
        std::shared_ptr<MusicPlayerInterface> musicPlayer = nullptr);

    void startGame(
        std::shared_ptr<GameState> InitialState, GameLoopFunctionPtr gameloop_function) override;

    void setupRenderTarget() override;
    void setRenderTarget(std::shared_ptr<jt::renderTarget> rt) override;
    std::shared_ptr<jt::renderTarget> getRenderTarget() const override;

    virtual std::shared_ptr<MusicPlayerInterface> getMusicPlayer() override;

    virtual std::shared_ptr<InputManagerInterface> input() override;

private:
    std::shared_ptr<jt::RenderWindowInterface> m_window { nullptr };
    // std::shared_ptr<sf::RenderWindow> m_renderWindow { nullptr };
    std::shared_ptr<jt::renderTarget> m_renderTarget { nullptr };

    std::shared_ptr<InputManagerInterface> m_input { nullptr };
    std::shared_ptr<MusicPlayerInterface> m_musicPlayer { nullptr };

    std::shared_ptr<sf::View> m_view { nullptr };

    // override functions from GameBase
    virtual void doUpdate(float const elapsed) override;
    virtual void doDraw() const override;

    void updateShake(float elapsed) override;
    void applyCamShakeToView();
    void removeCamShakeFromView();

    void setView(std::shared_ptr<sf::View> view);
    std::shared_ptr<sf::View> getView();
};

} // namespace jt
#endif
