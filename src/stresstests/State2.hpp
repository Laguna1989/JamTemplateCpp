#ifndef STRESSTEST_STATE_2_HPP_INCLUDEGUARD
#define STRESSTEST_STATE_2_HPP_INCLUDEGUARD

#include "GameState.hpp"
#include "ObjectGroup.hpp"
#include "Shape.hpp"
#include "Sprite.hpp"
#include "SwarmObject.hpp"
#include "Timer.hpp"
#include "TweenAlpha.hpp"
#include <iostream>
#include <vector>

class State2 : public jt::GameState {
private:
    jt::Shape::Sptr m_overlay;
    jt::Shape::Sptr m_sky;

    jt::ObjectGroup<SwarmObject>::Sptr m_SwarmObjects;

    void doInternalCreate() override;
    void doInternalUpdate(float const /*elapsed*/) override;
    void updateSwarm();
    void updateOneSwarmObject(const size_t& i, jt::Vector2& centerPos);
    void doInternalDraw() const override;

    void drawSky() const;
};

#endif
