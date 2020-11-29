#include "StateGame.hpp"
#include "Game.hpp"
#include "GameProperties.hpp"
#include "Hud.hpp"
#include "InputManager.hpp"
#include "SmartShape.hpp"
#include "SmartSprite.hpp"
#include "TweenAlpha.hpp"
#include "color.hpp"

void StateGame::doCreate()
{
    float w = static_cast<float>(GP::GetWindowSize().x());
    float h = static_cast<float>(GP::GetWindowSize().y());

    using jt::SmartShape;
    using jt::TweenAlpha;

    m_background = std::make_shared<SmartShape>();
    m_background->makeRect({ w, h });
    m_background->setColor(GP::PaletteBackground());
    m_background->update(0.0f);

    doCreateInternal();

    m_overlay = std::make_shared<SmartShape>();
    m_overlay->makeRect(jt::vector2 { w, h });
    m_overlay->setColor(jt::color { 0, 0, 0 });
    m_overlay->update(0);
    auto tw
        = TweenAlpha<SmartShape>::create(m_overlay, 0.5f, std::uint8_t { 255 }, std::uint8_t { 0 });
    tw->setSkipFrames();
    add(tw);

    m_hud = std::make_shared<Hud>();
    add(m_hud);
}

void StateGame::doInternalUpdate(float const elapsed)
{
    m_background->update(elapsed);
    m_sprite->update(elapsed);
    m_overlay->update(elapsed);

    if (jt::InputManager::justPressed(jt::KeyCode::T)) {
        m_sprite->flash(0.25f);
    }
}

void StateGame::doInternalDraw() const
{
    m_background->draw(getGame()->getRenderTarget());
    drawObjects();
    m_sprite->draw(getGame()->getRenderTarget());
    m_overlay->draw(getGame()->getRenderTarget());
}

void StateGame::doCreateInternal()
{

    m_sprite = std::make_shared<jt::SmartSprite>();
    m_sprite->loadSprite("assets/coin.png", jt::recti { 0, 0, 16, 16 });
    m_sprite->setPosition(jt::vector2 { 100, 100 });
}
