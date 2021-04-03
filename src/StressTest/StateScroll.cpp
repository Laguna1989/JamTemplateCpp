#include "StateScroll.hpp"
#include "InputManager.hpp"
#include "MathHelper.hpp"
#include "StateSelect.hpp"

void StateScroll::doInternalCreate()
{
    m_background = std::make_shared<jt::SmartShape>();
    m_background->makeRect(jt::Vector2 { 400.0f, 300.0f });
    m_background->setColor(jt::colors::Blue);
    m_background->setIgnoreCamMovement(true);

    m_shape1 = std::make_shared<jt::SmartShape>();
    m_shape1->makeRect(jt::Vector2 { 40.0f, 30.0f });
    m_shape1->setColor(jt::colors::Cyan);
    m_shape1->setPosition(jt::Vector2 { 100.0f, 100.0f });

    m_sprite = std::make_shared<jt::SmartSprite>();
    m_sprite->loadSprite("assets/wall.png");
    m_sprite->setPosition({ 250, 32 });

    m_anim = std::make_shared<jt::SmartAnimation>();
    m_anim->add("assets/coin.png", "idle", jt::Vector2u { 16, 16 },
        jt::MathHelper::vectorBetween(0U, 11U), 0.15f);
    m_anim->play("idle");
    m_anim->setColor(jt::colors::Red);
    m_anim->setPosition(jt::Vector2 { 200.0f, 200.0f });
}

void StateScroll::doInternalUpdate(float const elapsed)
{
    if (jt::InputManager::justPressed(jt::KeyCode::F1)
        || jt::InputManager::justPressed(jt::KeyCode::Escape)) {
        getGame()->switchState(std::make_shared<StateSelect>());
    }

    auto const scrollspeed = 50.0f;
    if (jt::InputManager::pressed(jt::KeyCode::D)) {
        getGame()->getCamera()->move(jt::Vector2 { scrollspeed * elapsed, 0.0f });
    } else if (jt::InputManager::pressed(jt::KeyCode::A)) {
        getGame()->getCamera()->move(jt::Vector2 { -scrollspeed * elapsed, 0.0f });
    }
    if (jt::InputManager::pressed(jt::KeyCode::W)) {
        getGame()->getCamera()->move(jt::Vector2 { 0.0f, -scrollspeed * elapsed });
    } else if (jt::InputManager::pressed(jt::KeyCode::S)) {
        getGame()->getCamera()->move(jt::Vector2 { 0.0f, scrollspeed * elapsed });
    }

    m_background->update(elapsed);
    m_shape1->update(elapsed);
    m_sprite->update(elapsed);
    m_anim->update(elapsed);
}

void StateScroll::doInternalDraw() const
{
    m_background->draw(getGame()->getRenderTarget());

    drawObjects();
    m_sprite->draw(getGame()->getRenderTarget());
    m_shape1->draw(getGame()->getRenderTarget());
    m_anim->draw(getGame()->getRenderTarget());
}
