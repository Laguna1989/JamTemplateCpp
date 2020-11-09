#include "Game.hpp"
#include "GameState.hpp"
#include "InputManager.hpp"
#include "Random.hpp"
#include "SmartObject.hpp"
#include <iostream>

namespace JamTemplate {

Game::Game(unsigned int w, unsigned int h, float zoom, std::string const& title)
    : m_state { nullptr }
    , m_renderWindow { std::make_shared<sf::RenderWindow>(
          sf::VideoMode(w, h), title, sf::Style::Close) }
    , m_zoom { zoom }
    , m_renderTarget { std::make_shared<sf::RenderTexture>() }
{
    // m_renderWindow->setFramerateLimit(60);
    m_renderWindow->setVerticalSyncEnabled(true);

    unsigned int scaledWidth = static_cast<unsigned int>(w / m_zoom);
    unsigned int scaledHeight = static_cast<unsigned int>(h / m_zoom);

    m_renderTarget->create(scaledWidth, scaledHeight);
    m_renderTarget->setSmooth(false);

    m_view
        = std::make_shared<sf::View>(sf::FloatRect(0, 0, (float)scaledWidth, (float)scaledHeight));
    m_view->setViewport(sf::FloatRect(0, 0, 1, 1));
}

float Game::getZoom() const { return m_zoom; }

void Game::switchState(std::shared_ptr<GameState> newState)
{
    // std::cout << "switchstate\n";
    if (newState == nullptr) {
        std::cerr << "cannot switch to nullptr state!" << std::endl;
        return;
    }
    m_nextState = newState;
    // if no state has been assigned yet, we can directly switch state here.
    if (m_state == nullptr) {
        doSwitchState();
    }
}

void Game::setRenderTarget(std::shared_ptr<sf::RenderTexture> rt) { m_renderTarget = rt; }
std::shared_ptr<sf::RenderTexture> Game::getRenderTarget() { return m_renderTarget; }

void Game::setRenderWindow(std::shared_ptr<sf::RenderWindow> w) { m_renderWindow = w; }
std::shared_ptr<sf::RenderWindow> Game::getRenderWindow() { return m_renderWindow; }

void Game::setView(std::shared_ptr<sf::View> view)
{
    m_view = view;
    if (m_renderTarget != nullptr)
        m_renderTarget->setView(*m_view);
}
std::shared_ptr<sf::View> Game::getView() { return m_view; }

sf::Vector2f Game::getCamOffset() { return m_CamOffset; }

void Game::setCamOffset(sf::Vector2f const& ofs) { m_CamOffset = ofs; }
void Game::moveCam(sf::Vector2f const& v) { m_CamOffset += v; }

void Game::shake(float t, float strength, float shakeInterval)
{
    m_shakeTimer = t;
    m_shakeStrength = strength;
    m_shakeInterval = m_shakeIntervalMax = shakeInterval;
}

std::weak_ptr<Game> Game::getPtr() { return shared_from_this(); }

void Game::doUpdate(float const elapsed)
{
    // std::cout << "game::update\n";

    if (m_nextState != nullptr) {
        doSwitchState();
        return;
    }
    if (m_state == nullptr)
        return;

    sf::Vector2f mpf = getRenderWindow()->mapPixelToCoords(
        sf::Mouse::getPosition(*getRenderWindow()), *getView());
    sf::Vector2f mpfs
        = getRenderWindow()->mapPixelToCoords(sf::Mouse::getPosition(*getRenderWindow())) / m_zoom;
    InputManager::update(mpf.x, mpf.y, mpfs.x, mpfs.y, elapsed);

    updateShake(elapsed);
    m_state->update(elapsed);

    sf::Vector2i camOffsetInt { static_cast<int>(m_CamOffset.x + getView()->getSize().x / 2),
        static_cast<int>(m_CamOffset.y + getView()->getSize().y / 2) };

    getView()->setCenter(
        sf::Vector2f { static_cast<float>(camOffsetInt.x), static_cast<float>(camOffsetInt.y) });
    SmartObject::setCamOffset(getView()->getCenter() - getView()->getSize() * 0.5f);
};

void Game::doDraw() const
{
    // clear the old image
    m_renderTarget->clear(m_backgroundColor);
    // m_renderWindow->clear(m_backgroundColor);

    if (m_state == nullptr)
        return;
    m_state->draw();

    // convert renderTexture to sprite and draw that.
    const sf::Texture& texture = m_renderTarget->getTexture();
    sf::Sprite spr(texture);
    // Note: RenderTexture has a bug and is displayed upside down.
    // This is corrected by the following two lines
    spr.setScale(sf::Vector2f(m_zoom, -m_zoom));
    spr.setPosition(0.0f, static_cast<float>(m_renderWindow->getSize().y));

    // draw the sprite
    m_renderWindow->draw(spr);

    // blit it to the screen
    m_renderWindow->display();
};

void Game::updateShake(float elapsed)
{
    if (m_shakeOffset.x != 0 || m_shakeOffset.y != 0) {
        getView()->move(-m_shakeOffset.x, -m_shakeOffset.y);
    }

    if (m_shakeTimer > 0) {

        m_shakeTimer -= elapsed;
        m_shakeInterval -= elapsed;
        if (m_shakeInterval < 0) {
            m_shakeInterval = m_shakeIntervalMax;
            m_shakeOffset.x = JamTemplate::Random::getFloat(-m_shakeStrength, m_shakeStrength);
            m_shakeOffset.y = JamTemplate::Random::getFloat(-m_shakeStrength, m_shakeStrength);
        }
    } else {
        m_shakeOffset.x = m_shakeOffset.y = 0;
    }

    auto v = getView();
    v->move(m_shakeOffset.x, m_shakeOffset.y);
    setView(v);
}

void Game::resetShake()
{
    if (m_shakeOffset.x != 0 || m_shakeOffset.y != 0) {
        getView()->move(-m_shakeOffset.x, -m_shakeOffset.y);
    }
    m_shakeOffset.x = m_shakeOffset.y = 0;
    m_shakeTimer = -1;
    m_shakeStrength = 0;
}

void Game::doSwitchState()
{
    m_state = m_nextState;
    m_nextState = nullptr;

    m_CamOffset = sf::Vector2f { 0.0f, 0.0f };
    m_state->setGameInstance(getPtr());
    m_state->create();

    JamTemplate::InputManager::reset();
    resetShake();
}

} // namespace JamTemplate
