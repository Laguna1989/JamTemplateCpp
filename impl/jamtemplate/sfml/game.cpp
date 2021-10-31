#include "game.hpp"
#include "cam_interface.hpp"
#include "drawable_impl.hpp"
#include "game_state.hpp"
#include "input_manager.hpp"
#include "rect.hpp"
#include "render_window.hpp"
#include "sprite.hpp"
#include "vector.hpp"
#include <iostream>

namespace {
void horizontalFlip(std::unique_ptr<jt::Sprite> const& spr, float zoom, float window_size_y)
{
    spr->setScale(jt::Vector2 { zoom, -zoom });
    spr->setPosition({ spr->getPosition().x(), spr->getPosition().y() + window_size_y });
    spr->update(0.0f);
}
} // namespace

namespace jt {

Game::Game(std::shared_ptr<RenderWindowInterface> window, float zoom,
    std::shared_ptr<InputManagerInterface> input, std::shared_ptr<MusicPlayerInterface> musicPlayer,
    std::shared_ptr<CamInterface> camera)
    : GameBase { camera }
    , m_window { window }
    , m_input { input }
    , m_musicPlayer { musicPlayer }
{
    m_camera->setZoom(zoom);
    m_sprite_for_drawing = std::make_unique<jt::Sprite>();
}

std::shared_ptr<InputManagerInterface> Game::input() { return m_input; }

void Game::setupRenderTarget()
{
    m_renderTarget = m_window->createRenderTarget();
    auto const windowSize = m_window->getSize();
    auto const zoom = getCamera()->getZoom();
    auto const scaledWidth = static_cast<unsigned int>(windowSize.x() / zoom);
    auto const scaledHeight = static_cast<unsigned int>(windowSize.y() / zoom);

    m_renderTarget->create(scaledWidth, scaledHeight);
    m_renderTarget->setSmooth(false);

    m_view = std::make_shared<sf::View>(
        jt::Rect(0, 0, static_cast<float>(scaledWidth), static_cast<float>(scaledHeight)));
    m_view->setViewport(jt::Rect(0, 0, 1, 1));
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

void Game::doUpdate(float const elapsed)
{
    if (m_state == nullptr) {
        return;
    }
    m_state->update(elapsed);
    getCamera()->update(elapsed);

    if (m_window == nullptr) {
        return;
    }
    jt::Vector2 const mpf = m_window->getMousePosition() / getCamera()->getZoom();

    if (input()) {
        input()->update(MousePosition { mpf.x() + getCamera()->getCamOffset().x(),
            mpf.y() + getCamera()->getCamOffset().y(), mpf.x(), mpf.y() });
    }
    if (m_view) {
        int const camOffsetix { static_cast<int>(
            getCamera()->getCamOffset().x() + m_view->getSize().x / 2) };
        int const camOffsetiy { static_cast<int>(
            getCamera()->getCamOffset().y() + m_view->getSize().y / 2) };

        m_view->setCenter(
            jt::Vector2 { static_cast<float>(camOffsetix), static_cast<float>(camOffsetiy) });
        DrawableImpl::setCamOffset(-1.0f * (m_view->getCenter() - m_view->getSize() / 2.0f));
    }
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

    m_renderTarget->setView(*m_view);
    // convert renderTexture to sprite and draw that.
    const sf::Texture& texture = m_renderTarget->getTexture();

    m_sprite_for_drawing->fromTexture(texture);
    auto const shakeOffset = getCamera()->getShakeOffset();
    m_sprite_for_drawing->setPosition(shakeOffset);
    // Note: RenderTexture has a bug and is displayed upside down.
    horizontalFlip(m_sprite_for_drawing, getCamera()->getZoom(), m_window->getSize().y());

    // draw the sprite
    m_window->draw(m_sprite_for_drawing);

    // blit it to the screen
    m_window->display();
}

std::shared_ptr<jt::RenderWindowInterface> Game::getRenderWindow() const { return m_window; }

} // namespace jt
