#ifndef STRESSTEST_STATE_ROPE_HPP_INCLUDEGUARD
#define STRESSTEST_STATE_ROPE_HPP_INCLUDEGUARD

#include "game_state.hpp"
#include "vector.hpp"
#include <vector>

struct RopeMass {
    RopeMass(jt::Vector2 pos, float m);
    jt::Vector2 position;
    jt::Vector2 velocity;
    jt::Vector2 acceleration;
    float mass;
    bool fixed;
};

class StateRope : public jt::GameState {
private:
    jt::Vector2 getRopeMassPosition(int i) const;
    std::shared_ptr<RopeMass> createRopeMassPointer(int i) const;
    void createSingleRopeMass(int i);
    void createAllRopeMasses();
    void doInternalCreate() override;
    void resetAccelerations();
    void integrationStep(float elapsed);
    void calculateRopeForces();
    void doInternalUpdate(float elapsed) override;
    void doInternalDraw() const override;

    std::vector<std::shared_ptr<RopeMass>> m_rope_elements;
    jt::Vector2 const m_ropeStartingPoint { 200.0f, 20.0f };
    float const m_springConstant { 3000.0f };
};

#endif
