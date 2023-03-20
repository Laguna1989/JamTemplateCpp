#include "state_easing.hpp"
#include <control_command_move_cam.hpp>
#include <ease/bounce.hpp>
#include <ease/elastic.hpp>
#include <ease/expo.hpp>
#include <ease/linear.hpp>
#include <ease/sine.hpp>
#include <easing/ease_object.hpp>
#include <game_interface.hpp>
#include <state_select.hpp>

void StateEasing::onCreate()
{

    add(std::make_shared<EaseObject>(
        "bounce i", jt::ease::bounce::easeIn, jt::Vector2f { 1.0f, 0.0f }));
    add(std::make_shared<EaseObject>(
        "bounce o", jt::ease::bounce::easeOut, jt::Vector2f { 1.0f, 1.0f }));
    add(std::make_shared<EaseObject>(
        "bounce io", jt::ease::bounce::easeInOut, jt::Vector2f { 1.0f, 2.0f }));

    add(std::make_shared<EaseObject>(
        "elastic i", jt::ease::elastic::easeIn, jt::Vector2f { 4.0f, 0.0f }));
    add(std::make_shared<EaseObject>(
        "elastic o", jt::ease::elastic::easeOut, jt::Vector2f { 4.0f, 1.0f }));
    add(std::make_shared<EaseObject>(
        "elastic io", jt::ease::elastic::easeInOut, jt::Vector2f { 4.0f, 2.0f }));

    add(std::make_shared<EaseObject>(
        "expo i", jt::ease::expo::easeIn, jt::Vector2f { 5.0f, 0.0f }));
    add(std::make_shared<EaseObject>(
        "expo o", jt::ease::expo::easeOut, jt::Vector2f { 5.0f, 1.0f }));
    add(std::make_shared<EaseObject>(
        "expo io", jt::ease::expo::easeInOut, jt::Vector2f { 5.0f, 2.0f }));

    add(std::make_shared<EaseObject>(
        "linear n", jt::ease::linear::easeNone, jt::Vector2f { 6.0f, 0.0f }));
    add(std::make_shared<EaseObject>(
        "linear i", jt::ease::linear::easeIn, jt::Vector2f { 6.0f, 1.0f }));
    add(std::make_shared<EaseObject>(
        "linear o", jt::ease::linear::easeOut, jt::Vector2f { 6.0f, 2.0f }));
    add(std::make_shared<EaseObject>(
        "linear io", jt::ease::linear::easeInOut, jt::Vector2f { 6.0f, 3.0f }));

    add(std::make_shared<EaseObject>(
        "sine i", jt::ease::sine::easeIn, jt::Vector2f { 10.0f, 0.0f }));
    add(std::make_shared<EaseObject>(
        "sine o", jt::ease::sine::easeOut, jt::Vector2f { 10.0f, 1.0f }));
    add(std::make_shared<EaseObject>(
        "sine io", jt::ease::sine::easeInOut, jt::Vector2f { 10.0f, 2.0f }));

    float const scrollSpeed = 150.0f;
    getGame()->input().keyboard()->setCommandPressed({ jt::KeyCode::A, jt::KeyCode::Left },
        std::make_shared<ControlCommandMoveCam>(
            jt::Vector2f { -scrollSpeed, 0.0f }, getGame()->gfx().camera()));

    getGame()->input().keyboard()->setCommandPressed({ jt::KeyCode::D, jt::KeyCode::Right },
        std::make_shared<ControlCommandMoveCam>(
            jt::Vector2f { scrollSpeed, 0.0f }, getGame()->gfx().camera()));
}
void StateEasing::onEnter() { }

void StateEasing::onUpdate(float /*elapsed*/)
{
    if (getGame()->input().keyboard()->justPressed(jt::KeyCode::F1)
        || getGame()->input().keyboard()->justPressed(jt::KeyCode::Escape)) {
        getGame()->stateManager().switchState(std::make_shared<StateSelect>());
    }
}

void StateEasing::onDraw() const { }
