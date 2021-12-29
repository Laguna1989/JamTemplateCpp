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

Game::Game(GfxInterface& gfx, InputManagerInterface& input, MusicPlayerInterface& musicPlayer,
    StateManagerInterface& stateManager, LoggerInterface& logger,
    ActionCommandManagerInterface& actionCommandManager)
    : GameBase { gfx, input, musicPlayer, stateManager, logger, actionCommandManager }
{
    m_sprite_for_drawing = std::make_unique<jt::Sprite>();
    m_logger.debug("Game constructor done", { "jt" });
    setupRenderTarget();
}

void Game::setupRenderTarget()
{
    m_logger.debug("Game setupRenderTarget", { "jt" });
    auto const windowSize = gfx().window().getSize();
    auto const zoom = getCamera().getZoom();
    auto const scaledWidth = static_cast<unsigned int>(windowSize.x / zoom);
    auto const scaledHeight = static_cast<unsigned int>(windowSize.y / zoom);

    // TODO move view to gfxImpl
    m_view = std::make_shared<sf::View>(toLib(
        jt::Rectf { 0, 0, static_cast<float>(scaledWidth), static_cast<float>(scaledHeight) }));
    m_view->setViewport(toLib(jt::Rectf { 0, 0, 1, 1 }));
}

void Game::startGame(GameLoopFunctionPtr gameloop_function)
{
    m_logger.debug("startGame", { "jt" });
    while (gfx().window().isOpen()) {
        gfx().window().checkForClose();
        gameloop_function();
    }
}

void Game::doUpdate(float const elapsed)
{
    m_logger.verbose("update game, elapsed=" + std::to_string(elapsed), { "jt" });
    getStateManager().getCurrentState()->update(elapsed);

    getCamera().update(elapsed);

    // TODO think about pulling mouse position into gfx
    jt::Vector2f const mpf = gfx().window().getMousePosition() / getCamera().getZoom();

    input().update(MousePosition { mpf.x + getCamera().getCamOffset().x,
                       mpf.y + getCamera().getCamOffset().y, mpf.x, mpf.y },
        elapsed);

    if (m_view) {
        int const camOffsetix { static_cast<int>(
            getCamera().getCamOffset().x + m_view->getSize().x / 2) };
        int const camOffsetiy { static_cast<int>(
            getCamera().getCamOffset().y + m_view->getSize().y / 2) };

        m_view->setCenter(toLib(
            jt::Vector2f { static_cast<float>(camOffsetix), static_cast<float>(camOffsetiy) }));
        DrawableImpl::setCamOffset(-1.0f * fromLib(m_view->getCenter() - m_view->getSize() / 2.0f));
    }
}

void Game::doDraw() const
{
    m_logger.verbose("draw game", { "jt" });
    auto target = gfx().target();
    if (!target) {
        return;
    }

    target->clear(sf::Color::Black);

    m_stateManager.getCurrentState()->draw();

    target->setView(*m_view);
    // convert renderTexture to sprite and draw that.
    const sf::Texture& texture = target->getTexture();

    m_sprite_for_drawing->fromTexture(texture);
    auto const shakeOffset = getCamera().getShakeOffset();
    m_sprite_for_drawing->setPosition(shakeOffset);
    // Note: RenderTexture has a bug and is displayed upside down.
    horizontalFlip(m_sprite_for_drawing, getCamera().getZoom(), gfx().window().getSize().y);

    gfx().window().draw(m_sprite_for_drawing);

    gfx().window().display();
}

} // namespace jt
