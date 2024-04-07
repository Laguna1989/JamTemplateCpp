#ifndef JAMTEMPLATE_STATE_WATER_HPP
#define JAMTEMPLATE_STATE_WATER_HPP

#include "shape.hpp"
#include <game_state.hpp>
#include <array>

class StateWater : public jt::GameState {
    void onCreate() override;
    void onEnter() override;
    void onUpdate(float elapsed) override;
    void onDraw() const override;

    float calculateDensity(jt::Vector2f const& samplePoint);

    jt::Vector2f calculatePressureForce(std::size_t particleIndex);

    float convertDensityToPressure(float density);
    float calculateSharedPressure(float densityA, float densityB);

    std::vector<jt::Vector2f> positions;
    std::vector<jt::Vector2f> predictedPositions;
    std::vector<jt::Vector2f> velocities;
    std::vector<float> densities;

    mutable jt::Vector2f gravity { 0.0f, 0.0f };
    mutable float smoothingRadius = 16.0f;
    mutable float mass = 1.0f;

    mutable float targetDensity = 1.0f;
    mutable float pressureMultiplier = 17.0f;

    mutable float dampingFactor = 0.99f;

    mutable std::shared_ptr<jt::DrawableInterface> shape;
};

#endif // JAMTEMPLATE_STATE_WATER_HPP
