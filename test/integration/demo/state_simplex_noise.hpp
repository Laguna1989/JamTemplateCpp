#ifndef GUARD_JAMTEMPLATE_STATE_SIMPLEX_NOISE_HPP
#define GUARD_JAMTEMPLATE_STATE_SIMPLEX_NOISE_HPP

#include "game_state.hpp"
#include "random/open_simplex_noise.hpp"

class StateSimplexNoise : public jt::GameState {
    void doInternalCreate() override;
    void doInternalUpdate(float elapsed) override;
    void doInternalDraw() const override;
    float m_z { 0.0f };
    jt::OpenSimplexNoise noise;
};

#endif // GUARD_JAMTEMPLATE_STATE_SIMPLEX_NOISE_HPP
