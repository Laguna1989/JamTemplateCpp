#include "state_easing.hpp"
#include "control_command_move_cam.hpp"
#include "ease/back.hpp"
#include "ease/bounce.hpp";
#include "ease/circ.hpp"
#include "ease/cubic.hpp"
#include "ease/elastic.hpp"
#include "ease_object.hpp"
#include "game_interface.hpp"
#include "state_select.hpp"

void StateEasing::doInternalCreate()
{
    float const offsetX = 16.0f;
    float const offsetY = 16.0f;
    float const spacingX = 80.0f;

    float const spacingY = 84.0f;

    add(std::make_shared<EaseObject>("back i", jt::ease::back::easeIn,
        jt::Vector2f { offsetX + 0 * spacingX, offsetY + spacingY * 0 }));
    add(std::make_shared<EaseObject>("back o", jt::ease::back::easeOut,
        jt::Vector2f { offsetX + 0 * spacingX, offsetY + spacingY * 1 }));
    add(std::make_shared<EaseObject>("back io", jt::ease::back::easeInOut,
        jt::Vector2f { offsetX + 0 * spacingX, offsetY + spacingY * 2 }));

    add(std::make_shared<EaseObject>("bounce i", jt::ease::bounce::easeIn,
        jt::Vector2f { offsetX + 1 * spacingX, offsetY + spacingY * 0 }));
    add(std::make_shared<EaseObject>("bounce o", jt::ease::bounce::easeOut,
        jt::Vector2f { offsetX + 1 * spacingX, offsetY + spacingY * 1 }));
    add(std::make_shared<EaseObject>("bounce io", jt::ease::bounce::easeInOut,
        jt::Vector2f { offsetX + 1 * spacingX, offsetY + spacingY * 2 }));

    add(std::make_shared<EaseObject>("circ i", jt::ease::circ::easeIn,
        jt::Vector2f { offsetX + 2 * spacingX, offsetY + spacingY * 0 }));
    add(std::make_shared<EaseObject>("circ o", jt::ease::circ::easeOut,
        jt::Vector2f { offsetX + 2 * spacingX, offsetY + spacingY * 1 }));
    add(std::make_shared<EaseObject>("circ io", jt::ease::circ::easeInOut,
        jt::Vector2f { offsetX + 2 * spacingX, offsetY + spacingY * 2 }));

    add(std::make_shared<EaseObject>("cubic i", jt::ease::cubic::easeIn,
        jt::Vector2f { offsetX + 3 * spacingX, offsetY + spacingY * 0 }));
    add(std::make_shared<EaseObject>("cubic o", jt::ease::cubic::easeOut,
        jt::Vector2f { offsetX + 3 * spacingX, offsetY + spacingY * 1 }));
    add(std::make_shared<EaseObject>("cubic io", jt::ease::cubic::easeInOut,
        jt::Vector2f { offsetX + 3 * spacingX, offsetY + spacingY * 2 }));

    add(std::make_shared<EaseObject>("elastic i", jt::ease::elastic::easeIn,
        jt::Vector2f { offsetX + 4 * spacingX, offsetY + spacingY * 0 }));
    add(std::make_shared<EaseObject>("elastic o", jt::ease::elastic::easeOut,
        jt::Vector2f { offsetX + 4 * spacingX, offsetY + spacingY * 1 }));
    add(std::make_shared<EaseObject>("elastic io", jt::ease::elastic::easeInOut,
        jt::Vector2f { offsetX + 4 * spacingX, offsetY + spacingY * 2 }));

    float const scrollSpeed = 50.0f;
    getGame()->input()->keyboard()->setCommandPressed({ jt::KeyCode::A, jt::KeyCode::Left },
        std::make_shared<ControlCommandMoveCam>(
            jt::Vector2f { -scrollSpeed, 0.0f }, getGame()->getCamera()));

    getGame()->input()->keyboard()->setCommandPressed({ jt::KeyCode::D, jt::KeyCode::Right },
        std::make_shared<ControlCommandMoveCam>(
            jt::Vector2f { scrollSpeed, 0.0f }, getGame()->getCamera()));
}

void StateEasing::doInternalUpdate(float elapsed)
{
    if (getGame()->input()->keyboard()->justPressed(jt::KeyCode::F1)
        || getGame()->input()->keyboard()->justPressed(jt::KeyCode::Escape)) {
        getGame()->getStateManager()->switchState(std::make_shared<StateSelect>());
    }
}

void StateEasing::doInternalDraw() const { }
