#include "state_easing.hpp"
#include "../control_command_move_cam.hpp"
#include "../state_select.hpp"
#include "ease/back.hpp"
#include "ease/bounce.hpp"
#include "ease/circ.hpp"
#include "ease/cubic.hpp"
#include "ease/elastic.hpp"
#include "ease/expo.hpp"
#include "ease/linear.hpp"
#include "ease/quad.hpp"
#include "ease/quart.hpp"
#include "ease/quint.hpp"
#include "ease/sine.hpp"
#include "ease_object.hpp"
#include "game_interface.hpp"

void StateEasing::doInternalCreate()
{
    add(std::make_shared<EaseObject>(
        "back i", jt::ease::back::easeIn, jt::Vector2f { 0.0f, 0.0f }));
    add(std::make_shared<EaseObject>(
        "back o", jt::ease::back::easeOut, jt::Vector2f { 0.0f, 1.0f }));
    add(std::make_shared<EaseObject>(
        "back io", jt::ease::back::easeInOut, jt::Vector2f { 0.0f, 2.0f }));

    add(std::make_shared<EaseObject>(
        "bounce i", jt::ease::bounce::easeIn, jt::Vector2f { 1.0f, 0.0f }));
    add(std::make_shared<EaseObject>(
        "bounce o", jt::ease::bounce::easeOut, jt::Vector2f { 1.0f, 1.0f }));
    add(std::make_shared<EaseObject>(
        "bounce io", jt::ease::bounce::easeInOut, jt::Vector2f { 1.0f, 2.0f }));

    add(std::make_shared<EaseObject>(
        "circ i", jt::ease::circ::easeIn, jt::Vector2f { 2.0f, 0.0f }));
    add(std::make_shared<EaseObject>(
        "circ o", jt::ease::circ::easeOut, jt::Vector2f { 2.0f, 1.0f }));
    add(std::make_shared<EaseObject>(
        "circ io", jt::ease::circ::easeInOut, jt::Vector2f { 2.0f, 2.0f }));

    add(std::make_shared<EaseObject>(
        "cubic i", jt::ease::cubic::easeIn, jt::Vector2f { 3.0f, 0.0f }));
    add(std::make_shared<EaseObject>(
        "cubic o", jt::ease::cubic::easeOut, jt::Vector2f { 3.0f, 1.0f }));
    add(std::make_shared<EaseObject>(
        "cubic io", jt::ease::cubic::easeInOut, jt::Vector2f { 3.0f, 2.0f }));

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
        "quad i", jt::ease::quad::easeIn, jt::Vector2f { 7.0f, 0.0f }));
    add(std::make_shared<EaseObject>(
        "quad o", jt::ease::quad::easeOut, jt::Vector2f { 7.0f, 1.0f }));
    add(std::make_shared<EaseObject>(
        "quad io", jt::ease::quad::easeInOut, jt::Vector2f { 7.0f, 2.0f }));

    add(std::make_shared<EaseObject>(
        "quart i", jt::ease::quart::easeIn, jt::Vector2f { 8.0f, 0.0f }));
    add(std::make_shared<EaseObject>(
        "quart o", jt::ease::quart::easeOut, jt::Vector2f { 8.0f, 1.0f }));
    add(std::make_shared<EaseObject>(
        "quart io", jt::ease::quart::easeInOut, jt::Vector2f { 8.0f, 2.0f }));

    add(std::make_shared<EaseObject>(
        "quint i", jt::ease::quint::easeIn, jt::Vector2f { 9.0f, 0.0f }));
    add(std::make_shared<EaseObject>(
        "quint o", jt::ease::quint::easeOut, jt::Vector2f { 9.0f, 1.0f }));
    add(std::make_shared<EaseObject>(
        "quint io", jt::ease::quint::easeInOut, jt::Vector2f { 9.0f, 2.0f }));

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

void StateEasing::doInternalUpdate(float /*elapsed*/)
{
    if (getGame()->input().keyboard()->justPressed(jt::KeyCode::F1)
        || getGame()->input().keyboard()->justPressed(jt::KeyCode::Escape)) {
        getGame()->getStateManager().switchState(std::make_shared<StateSelect>());
    }
}

void StateEasing::doInternalDraw() const { }
