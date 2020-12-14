#include "Game.hpp"
#include "GameState.hpp"
#include "InputManager.hpp"
#include "Random.hpp"
#include "SmartDrawable.hpp"
#include "rect.hpp"
#include "vector.hpp"
#include <iostream>

namespace jt {

Game::Game(unsigned int w, unsigned int h, float zoom, std::string const& title)
    : m_renderWindow { std::make_shared<sf::RenderWindow>(
        sf::VideoMode(w, h), title, sf::Style::Close) }
    , m_zoom { zoom }
    , m_renderTarget { std::make_shared<jt::renderTarget>() }
{
    m_renderWindow->setVerticalSyncEnabled(true);

    unsigned int scaledWidth = static_cast<unsigned int>(w / m_zoom);
    unsigned int scaledHeight = static_cast<unsigned int>(h / m_zoom);

    m_renderTarget->create(scaledWidth, scaledHeight);
    m_renderTarget->setSmooth(false);

    m_view = std::make_shared<sf::View>(jt::rect(0, 0, (float)scaledWidth, (float)scaledHeight));
    m_view->setViewport(jt::rect(0, 0, 1, 1));
}

float Game::getZoom() const { return m_zoom; }

void Game::runGame(std::shared_ptr<GameState> InitialState, GameLoopFunctionPtr gameloop_function)
{
    switchState(InitialState);
    while (m_renderWindow->isOpen()) {
        sf::Event event;
        while (m_renderWindow->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                m_renderWindow->close();
            }
        }
        gameloop_function();
    }
}

void Game::setRenderTarget(std::shared_ptr<jt::renderTarget> rt)
{
    if (rt == nullptr) {
        throw std::invalid_argument { "cannot set nullptr rendertarget" };
    }
    m_renderTarget = rt;
}
std::shared_ptr<jt::renderTarget> Game::getRenderTarget() const { return m_renderTarget; }

void Game::setRenderWindow(std::shared_ptr<sf::RenderWindow> w)
{
    if (w == nullptr) {
        throw std::invalid_argument { "cannot set nullptr renderwindow" };
    }
    m_renderWindow = w;
}
std::shared_ptr<sf::RenderWindow> Game::getRenderWindow() { return m_renderWindow; }

void Game::setView(std::shared_ptr<sf::View> view)
{
    m_view = view;
    if (m_renderTarget != nullptr)
        m_renderTarget->setView(*m_view);
}
std::shared_ptr<sf::View> Game::getView() { return m_view; }

void Game::doUpdate(float const elapsed)
{
    if (m_state == nullptr) {
        return;
    }
    m_state->update(elapsed);

    jt::vector2 mpf = getRenderWindow()->mapPixelToCoords(
        sf::Mouse::getPosition(*getRenderWindow()), *getView());
    jt::vector2 mpfs
        = getRenderWindow()->mapPixelToCoords(sf::Mouse::getPosition(*getRenderWindow())) / m_zoom;
    InputManager::update(mpf.x(), mpf.y(), mpfs.x(), mpfs.y(), elapsed);

    int const camOffsetix { static_cast<int>(m_CamOffset.x() + getView()->getSize().x / 2) };
    int const camOffsetiy { static_cast<int>(m_CamOffset.y() + getView()->getSize().y / 2) };

    getView()->setCenter(
        jt::vector2 { static_cast<float>(camOffsetix), static_cast<float>(camOffsetiy) });
    SmartDrawable::setCamOffset(getView()->getCenter() - getView()->getSize() * 0.5f);
};

void Game::doDraw() const
{
    // clear the old image
    m_renderTarget->clear(m_backgroundColor);

    if (m_state == nullptr) {
        return;
    }

    m_state->draw();

    // convert renderTexture to sprite and draw that.
    const sf::Texture& texture = m_renderTarget->getTexture();
    sf::Sprite spr(texture);
    // Note: RenderTexture has a bug and is displayed upside down.
    // This is corrected by the following two lines
    spr.setScale(jt::vector2(m_zoom, -m_zoom));
    spr.setPosition(0.0f, static_cast<float>(m_renderWindow->getSize().y));

    // draw the sprite
    m_renderWindow->draw(spr);

    // blit it to the screen
    m_renderWindow->display();
};

void Game::updateShake(float elapsed)
{
    if (m_shakeOffset.x() != 0 || m_shakeOffset.y() != 0) {
        getView()->move(-m_shakeOffset.x(), -m_shakeOffset.y());
    }

    if (m_shakeTimer > 0) {

        m_shakeTimer -= elapsed;
        m_shakeInterval -= elapsed;
        if (m_shakeInterval < 0) {
            m_shakeInterval = m_shakeIntervalMax;
            m_shakeOffset.x() = jt::Random::getFloat(-m_shakeStrength, m_shakeStrength);
            m_shakeOffset.y() = jt::Random::getFloat(-m_shakeStrength, m_shakeStrength);
        }
    } else {
        m_shakeOffset.x() = m_shakeOffset.y() = 0;
    }

    auto v = getView();
    v->move(m_shakeOffset.x(), m_shakeOffset.y());
    setView(v);
}

void Game::resetShake()
{
    if (m_shakeOffset.x() != 0 || m_shakeOffset.y() != 0) {
        getView()->move(-m_shakeOffset.x(), -m_shakeOffset.y());
    }
    m_shakeOffset.x() = m_shakeOffset.y() = 0;
    m_shakeTimer = -1;
    m_shakeStrength = 0;
}

void Game::PlayMusic(std::string const& fileName)
{
    m_music = std::make_shared<sf::Music>();
    m_music->openFromFile(fileName);
    m_music->play();
    m_music->setLoop(true);
}
void Game::StopMusic()
{
    if (m_music) {
        m_music->stop();
    }
}
void Game::SetMusicVolume(float v)
{
    if (m_music) {
        m_music->setVolume(v);
    }
}

} // namespace jt
