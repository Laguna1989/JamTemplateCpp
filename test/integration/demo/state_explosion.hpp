#ifndef STRESSTEST_STATE_1_HPP_INCLUDEGUARD
#define STRESSTEST_STATE_1_HPP_INCLUDEGUARD

#include "game_state.hpp"

class StateExplosion : public jt::GameState {
private:
    void doInternalCreate() override;
    void doInternalUpdate(float const /*elapsed*/) override;
    void doInternalDraw() const override {};
};

#endif
