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

    void calculateParticleLookup();
    int getCellIndex(jt::Vector2f const& pos);
    int getCellIndex(int cx, int cy);

    std::vector<jt::Vector2f> positions;
    std::vector<jt::Vector2f> predictedPositions;
    std::vector<jt::Vector2f> velocities;
    std::vector<float> densities;
    std::map<int, std::vector<std::size_t>> particleLookup; // cellID, vector of particle IDs

    mutable jt::Vector2f gravity { 0.0f, 10.0f };
    mutable float smoothingRadius = 16.0f;
    mutable float mass = 1.0f;

    mutable float targetDensity = 5.0f;
    mutable float pressureMultiplier = 2.0f;

    mutable float dampingFactor = 0.99f;

    int numberOfCellsPerLine = 1;

    mutable std::shared_ptr<jt::DrawableInterface> shape;
};

#endif // JAMTEMPLATE_STATE_WATER_HPP
