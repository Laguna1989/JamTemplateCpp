#include "StateGame.hpp"
#include "Color.hpp"
#include "Game.hpp"
#include "GameProperties.hpp"
#include "Hud.hpp"
#include "InputManager.hpp"
#include "SmartShape.hpp"
#include "SmartSprite.hpp"
#include "StateMenu.hpp"
#include "TweenAlpha.hpp"

void StateGame::doInternalCreate()
{
    float const w = static_cast<float>(GP::GetWindowSize().x());
    float const h = static_cast<float>(GP::GetWindowSize().y());

    using jt::SmartShape;
    using jt::TweenAlpha;

    m_background = std::make_shared<SmartShape>();
    m_background->makeRect({ w, h });
    m_background->setColor(GP::PaletteBackground());
    m_background->update(0.0f);

    m_overlay = std::make_shared<SmartShape>();
    m_overlay->makeRect(jt::Vector2 { w, h });
    m_overlay->setColor(jt::Color { 0, 0, 0 });
    m_overlay->update(0);
    auto tw
        = TweenAlpha<SmartShape>::create(m_overlay, 0.5f, std::uint8_t { 255 }, std::uint8_t { 0 });
    tw->setSkipFrames();
    add(tw);

    m_sprite = std::make_shared<jt::SmartSprite>();
    m_sprite->loadSprite("assets/coin.png", jt::Recti { 0, 0, 16, 16 });
    m_sprite->setPosition(jt::Vector2 { 100, 100 });

    m_hud = std::make_shared<Hud>();
    add(m_hud);

    // StateGame will call drawObjects itself.
    setAutoDraw(false);
}

void StateGame::doInternalUpdate(float const elapsed)
{
    m_background->update(elapsed);
    m_sprite->update(elapsed);
    m_overlay->update(elapsed);

    if (jt::InputManager::justPressed(jt::KeyCode::T)) {
        m_sprite->flash(0.25f);
    }
    if (jt::InputManager::justPressed(jt::MouseButtonCode::MBLeft)) {
        m_sprite->flash(0.25f, jt::colors::Red);
    }
}

void StateGame::doInternalDraw() const
{
    m_background->draw(getGame()->getRenderTarget());
    drawObjects();
    m_sprite->draw(getGame()->getRenderTarget());
    m_overlay->draw(getGame()->getRenderTarget());
}
