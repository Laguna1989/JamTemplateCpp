#ifndef STRESSTEST_STATE_2_HPP
#define STRESSTEST_STATE_2_HPP

#include <game_state.hpp>
#include <object_group.hpp>
#include <shape.hpp>
#include <sprite.hpp>
#include <swarmobjects/swarm_object.hpp>

class StateSwarmObjects : public jt::GameState {
public:
    std::string getName() const override;

private:
    jt::Shape::Sptr m_sky;

    jt::ObjectGroup<SwarmObject>::Sptr m_SwarmObjects;

    void onCreate() override;
    void onEnter() override;
    void onUpdate(float const /*elapsed*/) override;
    void updateSwarm();
    void updateOneSwarmObject(const size_t& firstSwarmObjectIndex);
    void onDraw() const override;

    void drawSky() const;
};

#endif
