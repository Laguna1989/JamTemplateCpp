#ifndef JAMTEMPLATE_STATE_SIMPLEX_NOISE_HPP
#define JAMTEMPLATE_STATE_SIMPLEX_NOISE_HPP

#include <game_state.hpp>
#include <random/open_simplex_noise3d.hpp>

// TODO Rewrite in a way that all images are created upfront and then only drawn -> speed up
// performance
class State3DNoise : public jt::GameState {
    void onCreate() override;
    void onEnter() override;
    void onUpdate(float elapsed) override;
    void onDraw() const override;
    float m_z { 0.0f };
    jt::OpenSimplexNoise3D noiseL1 { 123 };
    jt::OpenSimplexNoise3D noiseL2 { 234 };
    jt::OpenSimplexNoise3D noiseL3 { 345 };
};

#endif // JAMTEMPLATE_STATE_SIMPLEX_NOISE_HPP
