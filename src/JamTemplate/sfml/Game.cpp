#include "Game.hpp"
#include "Camera.hpp"
#include "DrawableImpl.hpp"
#include "GameState.hpp"
#include "InputManager.hpp"
#include "Random.hpp"
#include "Rect.hpp"
#include "RenderWindow.hpp"
#include "Sprite.hpp"
#include "Vector.hpp"
#include <iostream>

namespace {
void horizontalFlip(std::shared_ptr<jt::Sprite> spr, float zoom, float window_size_y)
{
    spr->setScale(jt::Vector2 { zoom, -zoom });
    spr->setPosition({ 0.0f, window_size_y });
    spr->update(0.0f);
}
} // namespace

namespace jt {

Game::Game(std::shared_ptr<RenderWindowInterface> window, float zoom,
    std::shared_ptr<InputManagerInterface> input, std::shared_ptr<MusicPlayerInterface> musicPlayer)
    : m_window { window }
    , m_input { input }
    , m_musicPlayer { musicPlayer }
{
    m_camera->setZoom(zoom);
}

std::shared_ptr<InputManagerInterface> Game::input() { return m_input; }

void Game::setupRenderTarget()
{
    m_renderTarget = m_window->createRenderTarget();

    auto const windowSize = m_window->getSize();
    auto const zoom = getCamera()->getZoom();
    unsigned int const scaledWidth = static_cast<unsigned int>(windowSize.x() / zoom);
    unsigned int const scaledHeight = static_cast<unsigned int>(windowSize.y() / zoom);

    m_renderTarget->create(scaledWidth, scaledHeight);
    m_renderTarget->setSmooth(false);

    m_view = std::make_shared<sf::View>(jt::Rect(0, 0, (float)scaledWidth, (float)scaledHeight));
    m_view->setViewport(jt::Rect(0, 0, 1, 1));

    jt::RenderWindow::s_view = m_view;
}

std::shared_ptr<MusicPlayerInterface> Game::getMusicPlayer() { return m_musicPlayer; }

void Game::startGame(std::shared_ptr<GameState> InitialState, GameLoopFunctionPtr gameloop_function)
{
    switchState(InitialState);
    while (m_window->isOpen()) {
        m_window->checkForClose();
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

void Game::setView(std::shared_ptr<sf::View> view)
{
    m_view = view;
    if (m_renderTarget != nullptr) {
        m_renderTarget->setView(*m_view);
    }
}
std::shared_ptr<sf::View> Game::getView() { return m_view; }

void Game::doUpdate(float const elapsed)
{
    if (m_renderTarget == nullptr) {
        return;
    }
    if (m_state == nullptr) {
        return;
    }
    m_state->update(elapsed);

    jt::Vector2 mpf = m_window->getMousePosition();

    jt::Vector2 mpfs = m_window->getMousePositionScreen(getCamera()->getZoom());

    input()->mouse()->updateMousePosition(MousePosition { mpf.x(), mpf.y(), mpfs.x(), mpfs.y() });
    input()->mouse()->updateButtons();
    input()->keyboard()->updateKeys();

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
    if (!m_renderTarget) {
        return;
    }

    // clear the old image
    m_renderTarget->clear(m_backgroundColor);

    if (m_state == nullptr) {
        return;
    }

    m_state->draw();

    // convert renderTexture to sprite and draw that.
    const sf::Texture& texture = m_renderTarget->getTexture();

    // sf::Sprite spr(texture);
    std::shared_ptr<jt::Sprite> spr = std::make_shared<jt::Sprite>();
    spr->fromTexture(texture);

    // Note: RenderTexture has a bug and is displayed upside down.
    horizontalFlip(spr, getCamera()->getZoom(), m_window->getSize().y());

    // draw the sprite
    m_window->draw(spr);

    // blit it to the screen
    m_window->display();
}

void Game::updateShake(float elapsed)
{
    removeCamShakeFromView();

    getCamera()->update(elapsed);

    applyCamShakeToView();
}

void jt::Game::applyCamShakeToView()
{
    if (m_renderTarget == nullptr) {
        return;
    }
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
