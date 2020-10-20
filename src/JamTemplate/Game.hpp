#ifndef JAMTEMPLATE_GAME_HPP_INCLUDEGUARD
#define JAMTEMPLATE_GAME_HPP_INCLUDEGUARD

#include "GameObject.hpp"
#include <SFML/Graphics.hpp>
#include <memory>
#include <string>

namespace JamTemplate {

class GameState;

class Game final : public GameObject, public std::enable_shared_from_this<Game> {
public:
    using Sptr = std::shared_ptr<Game>;
    Game(unsigned int w, unsigned int h, float zoom, std::string const& title);

    float getZoom() const;

    // this function will likely be called from within update().
    // To ensure consisten behavior within one frame, the actual switching will take place in
    // doSwitchState() which will happen at the beginning of the next update loop.
    void switchState(std::shared_ptr<GameState> newState);

    void setRenderTarget(std::shared_ptr<sf::RenderTexture> rt);
    std::shared_ptr<sf::RenderTexture> getRenderTarget();

    void setRenderWindow(std::shared_ptr<sf::RenderWindow> w);
    std::shared_ptr<sf::RenderWindow> getRenderWindow();

    void setView(std::shared_ptr<sf::View> view);
    std::shared_ptr<sf::View> getView();

    sf::Vector2f getCamOffset();

    void shake(float t, float strength, float shakeInterval = 0.005f);

private:
    GameState::Sptr m_state { nullptr };
    GameState::Sptr m_nextState { nullptr };
    std::shared_ptr<sf::RenderTexture> m_renderTarget { nullptr };
    std::shared_ptr<sf::View> m_view { nullptr };
    std::shared_ptr<sf::RenderWindow> m_renderWindow { nullptr };

    float m_zoom;

    unsigned int m_windowWidth;
    unsigned int m_windowHeight;

    float m_shakeTimer { -1.0f };
    float m_shakeStrength { 0.0f };
    float m_shakeInterval { 0.0f };
    float m_shakeIntervalMax { 0.0f };
    sf::Vector2f m_shakeOffset { 0, 0 };

    sf::Color m_backgroundColor { sf::Color::Black };

    std::weak_ptr<Game> getPtr();

    virtual void doUpdate(float const elapsed) override;

    virtual void doDraw() const override;

    void updateShake(float elapsed);
    void resetShake();

    void doSwitchState();
};

}
#endif
