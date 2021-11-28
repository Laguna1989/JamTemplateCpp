#include "state_scroll.hpp"
#include "control_command_move_cam.hpp"
#include "drawable_helpers.hpp"
#include "game_interface.hpp"
#include "input/input_manager.hpp"
#include "math_helper.hpp"
#include "state_select.hpp"

void StateScroll::doInternalCreate()
{
    m_background = jt::dh::createShapeRect(jt::Vector2 { 400.0f, 300.0f }, jt::colors::Blue);
    m_background->setIgnoreCamMovement(true);

    m_shape1 = jt::dh::createShapeRect(jt::Vector2 { 40.0f, 30.0f }, jt::colors::Cyan);
    m_shape1->setPosition(jt::Vector2 { 100.0f, 100.0f });

    m_sprite = std::make_shared<jt::Sprite>();
    m_sprite->loadSprite("assets/wall.png");
    m_sprite->setPosition({ 250, 32 });

    m_anim = std::make_shared<jt::Animation>();
    m_anim->add("assets/coin.png", "idle", jt::Vector2u { 16, 16 },
        jt::MathHelper::numbersBetween(0U, 11U), 0.15f);
    m_anim->play("idle");
    m_anim->setColor(jt::colors::Red);
    m_anim->setPosition(jt::Vector2 { 200.0f, 200.0f });

    m_text_left_aligned = jt::dh::createText(getGame()->getRenderTarget(), "left aligned", 12);
    m_text_left_aligned->setTextAlign(jt::Text::TextAlign::LEFT);
    m_text_left_aligned->setPosition(jt::Vector2 { 300, 100 });

    m_text_center_aligned = jt::dh::createText(getGame()->getRenderTarget(), "center aligned", 12);
    m_text_center_aligned->setTextAlign(jt::Text::TextAlign::CENTER);
    m_text_center_aligned->setPosition(jt::Vector2 { 300, 130 });

    m_text_right_aligned = jt::dh::createText(getGame()->getRenderTarget(), "right aligned", 12);
    m_text_right_aligned->setTextAlign(jt::Text::TextAlign::RIGHT);
    m_text_right_aligned->setPosition(jt::Vector2 { 300, 160 });

    m_line = std::make_shared<jt::Line>(jt::Vector2 { 100, 50 });
    m_line->setPosition(jt::Vector2 { 20, 200 });

    float const scrollSpeed = 50.0f;
    getGame()->input()->keyboard()->setCommandPressed({ jt::KeyCode::W, jt::KeyCode::Up },
        std::make_shared<ControlCommandMoveCam>(
            jt::Vector2 { 0.0f, -scrollSpeed }, getGame()->getCamera()));

    getGame()->input()->keyboard()->setCommandPressed({ jt::KeyCode::A },
        std::make_shared<ControlCommandMoveCam>(
            jt::Vector2 { -scrollSpeed, 0.0f }, getGame()->getCamera()));

    getGame()->input()->keyboard()->setCommandPressed({ jt::KeyCode::S },
        std::make_shared<ControlCommandMoveCam>(
            jt::Vector2 { 0.0f, scrollSpeed }, getGame()->getCamera()));

    getGame()->input()->keyboard()->setCommandPressed({ jt::KeyCode::D },
        std::make_shared<ControlCommandMoveCam>(
            jt::Vector2 { scrollSpeed, 0.0f }, getGame()->getCamera()));
}

void StateScroll::doInternalUpdate(float const elapsed)
{
    if (getGame()->input()->keyboard()->justPressed(jt::KeyCode::F1)
        || getGame()->input()->keyboard()->justPressed(jt::KeyCode::Escape)) {
        getGame()->getStateManager()->switchState(std::make_shared<StateSelect>());
    }

    m_background->update(elapsed);
    m_shape1->update(elapsed);
    m_sprite->update(elapsed);
    m_anim->update(elapsed);

    m_text_left_aligned->update(elapsed);
    m_text_center_aligned->update(elapsed);
    m_text_right_aligned->update(elapsed);
    m_line->update(elapsed);
}

void StateScroll::doInternalDraw() const
{
    m_background->draw(getGame()->getRenderTarget());

    drawObjects();
    m_sprite->draw(getGame()->getRenderTarget());
    m_shape1->draw(getGame()->getRenderTarget());
    m_anim->draw(getGame()->getRenderTarget());

    m_text_left_aligned->draw(getGame()->getRenderTarget());
    m_text_center_aligned->draw(getGame()->getRenderTarget());
    m_text_right_aligned->draw(getGame()->getRenderTarget());

    m_line->draw(getGame()->getRenderTarget());
}
