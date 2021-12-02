#ifndef GUARD_JAMTEMPLATE_STATE_GRADIENT_HPP
#define GUARD_JAMTEMPLATE_STATE_GRADIENT_HPP

#include "game_state.hpp"
#include "shape.hpp"

class StateGradient : public jt::GameState {
    void doInternalCreate() override;
    void doInternalUpdate(float elapsed) override;
    void doInternalDraw() const override;

    std::vector<std::shared_ptr<jt::Shape>> m_shapes;
};

#endif // MYAWESOMEGAME_STATE_GRADIENT_HPP
