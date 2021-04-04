#include "Game.hpp"
#include "Camera.hpp"
#include "DrawableImpl.hpp"
#include "GameState.hpp"
#include "InputManager.hpp"
#include "Random.hpp"
#include "Rect.hpp"
#include "Vector.hpp"
#include <iostream>

namespace jt {

Game::Game(unsigned int w, unsigned int h, float zoom, std::string const& title,
    std::shared_ptr<MusicPlayerInterface> musicPlayer)
    : m_renderWindow { std::make_shared<sf::RenderWindow>(
        sf::VideoMode(w, h), title, sf::Style::Close) }
    , m_renderTarget { std::make_shared<jt::renderTarget>() }
    , m_musicPlayer { musicPlayer }
{
    m_camera->setZoom(zoom);
    m_renderWindow->setVerticalSyncEnabled(true);

    unsigned int const scaledWidth = static_cast<unsigned int>(w / zoom);
    unsigned int const scaledHeight = static_cast<unsigned int>(h / zoom);

    m_renderTarget->create(scaledWidth, scaledHeight);
    m_renderTarget->setSmooth(false);

    m_view = std::make_shared<sf::View>(jt::Rect(0, 0, (float)scaledWidth, (float)scaledHeight));
    m_view->setViewport(jt::Rect(0, 0, 1, 1));
}

std::shared_ptr<MusicPlayerInterface> Game::getMusicPlayer() { return m_musicPlayer; }

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

    jt::Vector2 mpf = getRenderWindow()->mapPixelToCoords(
        sf::Mouse::getPosition(*getRenderWindow()), *getView());
    jt::Vector2 mpfs
        = getRenderWindow()->mapPixelToCoords(sf::Mouse::getPosition(*getRenderWindow()))
        / getCamera()->getZoom();
    InputManager::update(mpf.x(), mpf.y(), mpfs.x(), mpfs.y(), elapsed);

    int const camOffsetix { static_cast<int>(
        getCamera()->getCamOffset().x() + getView()->getSize().x / 2) };
    int const camOffsetiy { static_cast<int>(
        getCamera()->getCamOffset().y() + getView()->getSize().y / 2) };

    getView()->setCenter(
        jt::Vector2 { static_cast<float>(camOffsetix), static_cast<float>(camOffsetiy) });
    DrawableImpl::setCamOffset(-1.0f * (getView()->getCenter() - getView()->getSize() / 2.0f));
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
    auto const zoom = getCamera()->getZoom();
    spr.setScale(jt::Vector2(zoom, -zoom));
    spr.setPosition(0.0f, static_cast<float>(m_renderWindow->getSize().y));

    // draw the sprite
    m_renderWindow->draw(spr);

    // blit it to the screen
    m_renderWindow->display();
};

void Game::updateShake(float elapsed)
{
    removeCamShakeFromView();

    getCamera()->update(elapsed);

    applyCamShakeToView();
}

void jt::Game::applyCamShakeToView()
{
    auto const newShakeOffset = getCamera()->getShakeOffset();
    auto v = getView();
    v->move(newShakeOffset.x(), newShakeOffset.y());
    setView(v);
}

void jt::Game::removeCamShakeFromView()
{
    auto const oldShakeOffset = getCamera()->getShakeOffset();
    if (oldShakeOffset.x() != 0 || oldShakeOffset.y() != 0) {
        getView()->move(-oldShakeOffset.x(), -oldShakeOffset.y());
    }
}

} // namespace jt
