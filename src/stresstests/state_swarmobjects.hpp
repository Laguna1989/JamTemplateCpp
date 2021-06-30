﻿#ifndef STRESSTEST_STATE_2_HPP_INCLUDEGUARD
#define STRESSTEST_STATE_2_HPP_INCLUDEGUARD

#include "game_state.hpp"
#include "object_group.hpp"
#include "shape.hpp"
#include "sprite.hpp"
#include "swarm_object.hpp"

class StateSwarmObjects : public jt::GameState {
private:
    jt::Shape::Sptr m_overlay;
    jt::Shape::Sptr m_sky;

    jt::ObjectGroup<SwarmObject>::Sptr m_SwarmObjects;

    void doInternalCreate() override;
    void doInternalUpdate(float const /*elapsed*/) override;
    void updateSwarm();
    void updateOneSwarmObject(const size_t& i, jt::Vector2 const& centerPos);
    void doInternalDraw() const override;

    void drawSky() const;
};

#endif
