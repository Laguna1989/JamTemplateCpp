#ifndef STRESSTEST_STATE_SCROLL_HPP_INCLUDEGUARD
#define STRESSTEST_STATE_SCROLL_HPP_INCLUDEGUARD

#include "Game.hpp"
#include "GameState.hpp"
#include "SmartAnimation.hpp"
#include "SmartShape.hpp"
#include "SmartSprite.hpp"
#include "TweenAlpha.hpp"
#include <cstdint>
#include <iostream>
#include <vector>

class StateScroll : public jt::GameState {
private:
    jt::SmartShape::Sptr m_shape1;
    jt::SmartAnimation::Sptr m_anim;
    jt::SmartSprite::Sptr m_sprite;
    jt::SmartShape::Sptr m_background;

    void doInternalCreate() override;
    void doInternalUpdate(float const /*elapsed*/) override;
    void doInternalDraw() const override;
};

#endif
