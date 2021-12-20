#ifndef STRESSTEST_STATE_1_HPP_INCLUDEGUARD
#define STRESSTEST_STATE_1_HPP_INCLUDEGUARD

#include "game_state.hpp"
#include <string>

class StateExplosion : public jt::GameState {
private:
    void doInternalCreate() override;

public:
    std::string getName() const override;

private:
    void doInternalUpdate(float const /*elapsed*/) override;
    void doInternalDraw() const override {};
};

#endif
