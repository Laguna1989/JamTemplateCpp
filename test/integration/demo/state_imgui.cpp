#include "state_imgui.hpp"
#include "game_interface.hpp"
#include "imgui.h"

void StateImGui::doInternalCreate() {
}

void StateImGui::doInternalUpdate(float elapsed) {
    getGame()->getRenderWindow()->updateGui(elapsed);
}

void StateImGui::doInternalDraw() const {
    ImGui::ShowDemoWindow();
    getGame()->getRenderWindow()->renderGui();

}
