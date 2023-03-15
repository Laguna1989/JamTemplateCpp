#ifndef STRESSTEST_STATE_ROPE_HPP
#define STRESSTEST_STATE_ROPE_HPP

#include <game_state.hpp>
#include <vector.hpp>
#include <string>
#include <vector>

struct RopeMass {
    RopeMass(jt::Vector2f pos, float m);
    jt::Vector2f position;
    jt::Vector2f velocity;
    jt::Vector2f acceleration;
    float mass;
    bool fixed;
};

class StateRope : public jt::GameState {
public:
    std::string getName() const override;

private:
    void onCreate() override;
    void onEnter() override;
    void onUpdate(float elapsed) override;
    void onDraw() const override;

    jt::Vector2f getRopeMassPosition(int i) const;
    std::shared_ptr<RopeMass> createRopeMassPointer(int i) const;
    void createSingleRopeMass(int i);
    void createAllRopeMasses();

    void resetAccelerations();
    void integrationStep(float elapsed);
    void calculateRopeForces();

    std::vector<std::shared_ptr<RopeMass>> m_rope_elements;
    jt::Vector2f const m_ropeStartingPoint { 200.0f, 20.0f };
    float const m_springConstant { 3000.0f };
};

#endif
