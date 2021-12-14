#ifndef GUARD_JAMTEMPLATE_STATE_SIMPLEX_NOISE_HPP
#define GUARD_JAMTEMPLATE_STATE_SIMPLEX_NOISE_HPP

#include "game_state.hpp"
#include "random/open_simplex_noise3d.hpp"

class StateSimplexNoise : public jt::GameState {
    void doInternalCreate() override;
    void doInternalUpdate(float elapsed) override;
    void doInternalDraw() const override;
    float m_z { 0.0f };
    jt::OpenSimplexNoise3D noiseL1 { 123 };
    jt::OpenSimplexNoise3D noiseL2 { 234 };
    jt::OpenSimplexNoise3D noiseL3 { 345 };
};

#endif // GUARD_JAMTEMPLATE_STATE_SIMPLEX_NOISE_HPP
