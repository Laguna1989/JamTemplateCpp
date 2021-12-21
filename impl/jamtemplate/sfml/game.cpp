#include "game.hpp"
#include "action_commands/basic_action_commands.hpp"
#include "drawable_impl.hpp"
#include "rect_lib.hpp"
#include "render_window.hpp"
#include "sprite.hpp"
#include "texture_manager_impl.hpp"
#include "vector.hpp"
#include "vector_lib.hpp"

namespace {
void horizontalFlip(std::unique_ptr<jt::Sprite> const& spr, float zoom, float window_size_y)
{
    spr->setScale(jt::Vector2f { zoom, -zoom });
    spr->setPosition({ spr->getPosition().x, spr->getPosition().y + window_size_y });
    spr->update(0.0f);
}
} // namespace

namespace jt {

Game::Game(std::shared_ptr<RenderWindowInterface> window,
    std::shared_ptr<InputManagerInterface> input, std::shared_ptr<MusicPlayerInterface> musicPlayer,
    std::shared_ptr<CamInterface> camera, std::shared_ptr<jt::StateManagerInterface> stateManager)
    : GameBase { window, input, musicPlayer, camera, stateManager }
{
    m_sprite_for_drawing = std::make_unique<jt::Sprite>();
    m_textureManager = std::make_shared<jt::TextureManagerImpl>();
    m_logger->debug("Game constructor done", { "jt" });
    setupRenderTarget();
}

void Game::setupRenderTarget()
{
    m_renderTarget = getRenderWindow()->createRenderTarget();
    if (m_renderTarget == nullptr) {
        return;
    }
    m_logger->debug("Game setupRenderTarget", { "jt" });
    auto const windowSize = getRenderWindow()->getSize();
    auto const zoom = getCamera()->getZoom();
    auto const scaledWidth = static_cast<unsigned int>(windowSize.x / zoom);
    auto const scaledHeight = static_cast<unsigned int>(windowSize.y / zoom);

    m_renderTarget->create(scaledWidth, scaledHeight);
    m_renderTarget->setSmooth(false);

    m_view = std::make_shared<sf::View>(toLib(
        jt::Rectf { 0, 0, static_cast<float>(scaledWidth), static_cast<float>(scaledHeight) }));
    m_view->setViewport(toLib(jt::Rectf { 0, 0, 1, 1 }));
}

void Game::startGame(GameLoopFunctionPtr gameloop_function)
{
    // cannot be done in constructor as this is not fully available
    addBasicActionCommands(*this);

    m_logger->debug("startGame", { "jt" });
    while (getRenderWindow()->isOpen()) {
        getRenderWindow()->checkForClose();
        gameloop_function();
    }
}

void Game::doUpdate(float const elapsed)
{
    m_logger->verbose("update game, elapsed=" + std::to_string(elapsed), { "jt" });
    m_stateManager->getCurrentState()->update(elapsed);

    getCamera()->update(elapsed);

    jt::Vector2f const mpf = getRenderWindow()->getMousePosition() / getCamera()->getZoom();

    input()->update(MousePosition { mpf.x + getCamera()->getCamOffset().x,
                        mpf.y + getCamera()->getCamOffset().y, mpf.x, mpf.y },
        elapsed);

    if (m_view) {
        int const camOffsetix { static_cast<int>(
            getCamera()->getCamOffset().x + m_view->getSize().x / 2) };
        int const camOffsetiy { static_cast<int>(
            getCamera()->getCamOffset().y + m_view->getSize().y / 2) };

        m_view->setCenter(toLib(
            jt::Vector2f { static_cast<float>(camOffsetix), static_cast<float>(camOffsetiy) }));
        DrawableImpl::setCamOffset(-1.0f * fromLib(m_view->getCenter() - m_view->getSize() / 2.0f));
    }
}

void Game::doDraw() const
{
    m_logger->verbose("draw game", { "jt" });
    if (!m_renderTarget) {
        return;
    }

    m_renderTarget->clear(sf::Color::Black);

    m_stateManager->getCurrentState()->draw();

    m_renderTarget->setView(*m_view);
    // convert renderTexture to sprite and draw that.
    const sf::Texture& texture = m_renderTarget->getTexture();

    m_sprite_for_drawing->fromTexture(texture);
    auto const shakeOffset = getCamera()->getShakeOffset();
    m_sprite_for_drawing->setPosition(shakeOffset);
    // Note: RenderTexture has a bug and is displayed upside down.
    horizontalFlip(m_sprite_for_drawing, getCamera()->getZoom(), getRenderWindow()->getSize().y);

    getRenderWindow()->draw(m_sprite_for_drawing);

    getRenderWindow()->display();
}

} // namespace jt
