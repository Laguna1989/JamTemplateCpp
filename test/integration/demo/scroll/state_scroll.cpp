#include "state_scroll.hpp"
#include <control_command_move_cam.hpp>
#include <drawable_helpers.hpp>
#include <game_interface.hpp>
#include <input/input_manager.hpp>
#include <math_helper.hpp>
#include <state_select.hpp>
#include <timer.hpp>

void StateScroll::doInternalCreate()
{
    m_background = jt::dh::createShapeRect(
        jt::Vector2f { 400.0f, 300.0f }, jt::Color { 20, 20, 150 }, textureManager());
    m_background->setIgnoreCamMovement(true);

    m_shape1 = jt::dh::createShapeRect(
        jt::Vector2f { 40.0f, 30.0f }, jt::colors::Cyan, textureManager());
    m_shape1->setPosition(jt::Vector2f { 100.0f, 100.0f });
    getGame()->gfx().createZLayer(5);
    m_shape1->setZ(5);

    m_shape2 = jt::dh::createShapeRect(
        jt::Vector2f { 40.0f, 30.0f }, jt::colors::Blue, textureManager());
    m_shape2->setPosition(jt::Vector2f { 120.0f, 115.0f });

    m_sprite
        = std::make_shared<jt::Sprite>("assets/test/integration/demo/wall.png", textureManager());
    m_sprite->setPosition({ 250, 32 });
    m_sprite->setOrigin(jt::OriginMode::CENTER);
    m_sprite->setShadow(jt::colors::Black, jt::Vector2f { 2, 2 });

    m_spriteCircle = std::make_shared<jt::Sprite>("#r#32", textureManager());
    m_spriteCircle->setPosition({ 350, 64 });

    m_anim = std::make_shared<jt::Animation>();
    m_anim->add("assets/test/integration/demo/coin.png", "idle", jt::Vector2u { 16, 16 },
        jt::MathHelper::numbersBetween(0U, 11U), 0.15f, textureManager());
    m_anim->play("idle");
    m_anim->setPosition(jt::Vector2f { 200.0f, 200.0f });

    m_text_left_aligned = jt::dh::createText(renderTarget(), "left aligned", 16);
    m_text_left_aligned->setTextAlign(jt::Text::TextAlign::LEFT);
    m_text_left_aligned->setPosition(jt::Vector2f { 300, 100 });

    m_text_center_aligned = jt::dh::createText(renderTarget(), "center aligned", 16);
    m_text_center_aligned->setTextAlign(jt::Text::TextAlign::CENTER);
    m_text_center_aligned->setPosition(jt::Vector2f { 300, 130 });

    m_text_right_aligned = jt::dh::createText(renderTarget(), "right aligned", 16);
    m_text_right_aligned->setTextAlign(jt::Text::TextAlign::RIGHT);
    m_text_right_aligned->setPosition(jt::Vector2f { 300, 160 });

    m_line = std::make_shared<jt::Line>(jt::Vector2f { 100, 50 });
    m_line->setPosition(jt::Vector2f { 20, 200 });

    float const scrollSpeed = 50.0f;
    getGame()->input().keyboard()->setCommandPressed({ jt::KeyCode::W, jt::KeyCode::Up },
        std::make_shared<ControlCommandMoveCam>(
            jt::Vector2f { 0.0f, -scrollSpeed }, getGame()->gfx().camera()));

    getGame()->input().keyboard()->setCommandPressed({ jt::KeyCode::A, jt::KeyCode::Left },
        std::make_shared<ControlCommandMoveCam>(
            jt::Vector2f { -scrollSpeed, 0.0f }, getGame()->gfx().camera()));

    getGame()->input().keyboard()->setCommandPressed({ jt::KeyCode::S, jt::KeyCode::Down },
        std::make_shared<ControlCommandMoveCam>(
            jt::Vector2f { 0.0f, scrollSpeed }, getGame()->gfx().camera()));

    getGame()->input().keyboard()->setCommandPressed({ jt::KeyCode::D, jt::KeyCode::Right },
        std::make_shared<ControlCommandMoveCam>(
            jt::Vector2f { scrollSpeed, 0.0f }, getGame()->gfx().camera()));

    auto t = std::make_shared<jt::Timer>(1.5f, [this]() { m_anim->shake(0.5f, 15.0f, 0.001f); });
    add(t);

    auto t2 = std::make_shared<jt::Timer>(1.5f, [this]() {
        m_sprite->flash(0.9f, jt::colors::Green);
        m_shape1->flash(0.5f, jt::colors::Red);
    });
    add(t2);

    auto t3 = std::make_shared<jt::Timer>(1.2f, [this]() { m_sprite->flicker(0.9f, 0.05f); });
    add(t3);
}

void StateScroll::doInternalUpdate(float const elapsed)
{
    if (getGame()->input().keyboard()->justPressed(jt::KeyCode::F1)
        || getGame()->input().keyboard()->justPressed(jt::KeyCode::Escape)) {
        getGame()->stateManager().switchState(std::make_shared<StateSelect>());
    }

    m_background->update(elapsed);
    m_shape1->setRotation(getAge() * 90);
    m_shape1->update(elapsed);

    m_shape2->update(elapsed);

    m_sprite->setRotation(-getAge() * 90);
    m_sprite->update(elapsed);

    m_spriteCircle->update(elapsed);

    m_anim->update(elapsed);

    m_text_left_aligned->update(elapsed);
    m_text_center_aligned->update(elapsed);
    m_text_right_aligned->update(elapsed);
    m_line->update(elapsed);
}

void StateScroll::doInternalDraw() const
{
    m_background->draw(renderTarget());

    drawObjects();
    m_sprite->draw(renderTarget());
    m_spriteCircle->draw(renderTarget());
    m_shape1->draw(renderTarget());
    m_shape2->draw(renderTarget());
    m_anim->draw(renderTarget());

    m_text_left_aligned->draw(renderTarget());
    m_text_center_aligned->draw(renderTarget());
    m_text_right_aligned->draw(renderTarget());

    m_line->draw(renderTarget());
}
std::string StateScroll::getName() const { return "Move Cam"; }
