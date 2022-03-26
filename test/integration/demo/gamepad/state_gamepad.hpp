#ifndef GUARD_JAMTEMPLATE_STATE_GAMEPAD_HPP
#define GUARD_JAMTEMPLATE_STATE_GAMEPAD_HPP

#include "game_state.hpp"
#include <memory>

namespace jt {
class Shape;
}

class StateGamepad : public jt::GameState {
private:
    void doInternalCreate() override;
    void doInternalUpdate(float elapsed) override;
    void doInternalDraw() const override;

    mutable std::shared_ptr<jt::Shape> m_backgroundShape { nullptr };
    mutable std::shared_ptr<jt::Shape> m_dotShape { nullptr };
};

#endif // GUARD_JAMTEMPLATE_STATE_GAMEPAD_HPP
