#include "state_gamepad.hpp"
#include <game_interface.hpp>
#include <gamepad/gamepad_visualizer.hpp>
#include <state_select.hpp>

void StateGamepad::doInternalCreate()
{
    for (auto i = 0; i != 3; ++i) {
        auto viz = std::make_shared<GamepadVisualizer>(i);
        add(viz);
    }
}

void StateGamepad::doInternalUpdate(float /*elapsed*/)
{

    if (getGame()->input().keyboard()->justPressed(jt::KeyCode::Escape)) {
        getGame()->stateManager().switchState(std::make_shared<StateSelect>());
    }
}

void StateGamepad::doInternalDraw() const { }
