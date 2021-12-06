#ifndef GUARD_JAMTEMPLATE_STATE_IMGUI_HPP
#define GUARD_JAMTEMPLATE_STATE_IMGUI_HPP

#include "console/log_interface.hpp"
#include "game_state.hpp"

namespace jt {
class Console;

} // namespace jt

class StateImGui : public ::jt::GameState {
    void doInternalCreate() override;
    void doInternalUpdate(float elapsed) override;
    void doInternalDraw() const override;

    std::shared_ptr<jt::Console> m_console;
    std::shared_ptr<jt::LogInterface> m_logger;
};

#endif // GUARD_JAMTEMPLATE_STATE_IMGUI_HPP
