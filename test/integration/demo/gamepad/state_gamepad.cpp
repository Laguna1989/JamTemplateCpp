#include "state_gamepad.hpp"
#include "game_interface.hpp"
#include "gamepad_visualizer.hpp"

void StateGamepad::doInternalCreate()
{
    for (auto i = 0; i != 3; ++i) {
        auto viz = std::make_shared<GamepadVisualizer>(i);
        add(viz);
    }
}

void StateGamepad::doInternalUpdate(float elapsed) { }

void StateGamepad::doInternalDraw() const { }
