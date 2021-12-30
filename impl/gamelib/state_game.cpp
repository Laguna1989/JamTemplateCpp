#include "state_game.hpp"
#include "box2dwrapper/box2d_world_impl.hpp"
#include "color.hpp"
#include "game_interface.hpp"
#include "game_properties.hpp"
#include "hud/hud.hpp"
#include "shape.hpp"
#include "sprite.hpp"
#include "state_menu.hpp"
#include "tweens/tween_alpha.hpp"

void StateGame::doInternalCreate()
{
    m_world = std::make_shared<jt::Box2DWorldImpl>(jt::Vector2f { 0.0f, 0.0f });

    float const w = static_cast<float>(GP::GetWindowSize().x);
    float const h = static_cast<float>(GP::GetWindowSize().y);

    using jt::Shape;
    using jt::TweenAlpha;

    m_background = std::make_shared<Shape>();
    m_background->makeRect({ w, h }, getGame()->gfx().textureManager());
    m_background->setColor(GP::PaletteBackground());
    m_background->setIgnoreCamMovement(true);
    m_background->update(0.0f);

    m_overlay = std::make_shared<Shape>();
    m_overlay->makeRect(jt::Vector2f { w, h }, getGame()->gfx().textureManager());
    m_overlay->setColor(jt::Color { 0, 0, 0 });
    m_overlay->setIgnoreCamMovement(true);
    m_overlay->update(0);
    auto tw = TweenAlpha::create(m_overlay, 0.5f, std::uint8_t { 255 }, std::uint8_t { 0 });
    tw->setSkipFrames();
    tw->addCompleteCallback([this]() { m_running = true; });
    add(tw);

    m_vignette = std::make_shared<jt::Sprite>("#v#"
            + std::to_string(static_cast<int>(GP::GetScreenSize().x)) + "#"
            + std::to_string(static_cast<int>(GP::GetScreenSize().y)),
        getGame()->gfx().textureManager());
    m_vignette->setIgnoreCamMovement(true);
    m_vignette->setColor({ 255, 255, 255, 100 });

    m_hud = std::make_shared<Hud>();
    add(m_hud);

    // StateGame will call drawObjects itself.
    setAutoDraw(false);
}

void StateGame::doInternalUpdate(float const elapsed)
{
    if (m_running) {
        m_world->step(elapsed, GP::PhysicVelocityIterations(), GP::PhysicPositionIterations());
        // update game logic here
        if (getGame()->input().keyboard()->justPressed(jt::KeyCode::A)) {
            m_scoreP1++;
            m_hud->getObserverScoreP1()->notify(m_scoreP1);
        }
        if (getGame()->input().keyboard()->justPressed(jt::KeyCode::D)) {
            m_scoreP2++;
            m_hud->getObserverScoreP2()->notify(m_scoreP2);
        }
    }

    m_background->update(elapsed);
    m_vignette->update(elapsed);
    m_overlay->update(elapsed);
}

void StateGame::doInternalDraw() const
{
    m_background->draw(getGame()->gfx().target());
    drawObjects();
    m_vignette->draw(getGame()->gfx().target());
    m_hud->draw();
    m_overlay->draw(getGame()->gfx().target());
}

void StateGame::endGame()
{
    if (m_hasEnded) {
        // trigger this function only once
        return;
    }
    m_hasEnded = true;
    m_running = false;

    auto tw = jt::TweenAlpha::create(m_overlay, 0.5f, std::uint8_t { 0 }, std::uint8_t { 255 });
    tw->setSkipFrames();
    tw->addCompleteCallback(
        [this]() { getGame()->getStateManager().switchState(std::make_shared<StateMenu>()); });
    add(tw);
}
std::string StateGame::getName() const { return "Game"; }
