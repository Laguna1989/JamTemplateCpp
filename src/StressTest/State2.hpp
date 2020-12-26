#ifndef STRESSTEST_STATE_2_HPP_INCLUDEGUARD
#define STRESSTEST_STATE_2_HPP_INCLUDEGUARD

#include "Game.hpp"
#include "GameState.hpp"
#include "ObjectGroup.hpp"
#include "SmartShape.hpp"
#include "SmartSprite.hpp"
#include "SwarmObject.hpp"
#include "Timer.hpp"
#include "TweenAlpha.hpp"
#include <iostream>
#include <vector>

class State2 : public jt::GameState {
private:
    jt::SmartShape::Sptr m_overlay;
    jt::SmartShape::Sptr m_sky;

    jt::ObjectGroup<SwarmObject>::Sptr m_SwarmObjects;

    void doInternalCreate() override;
    void doInternalUpdate(float const /*elapsed*/) override;
    void doInternalDraw() const override;

    void drawSky() const;
};

#endif
