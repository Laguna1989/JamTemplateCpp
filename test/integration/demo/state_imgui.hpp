#ifndef GUARD_JAMTEMPLATE_STATE_IMGUI_HPP
#define GUARD_JAMTEMPLATE_STATE_IMGUI_HPP

#include "game_state.hpp"
#include <string>

namespace jt {
class Console;

} // namespace jt

class StateImGui : public ::jt::GameState {
public:
    std::string getName() const override;

private:
    void doInternalCreate() override;
    void doInternalUpdate(float elapsed) override;
    void doInternalDraw() const override;

    std::shared_ptr<jt::Console> m_console;
};

#endif // GUARD_JAMTEMPLATE_STATE_IMGUI_HPP
