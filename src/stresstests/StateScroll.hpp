#ifndef STRESSTEST_STATE_SCROLL_HPP_INCLUDEGUARD
#define STRESSTEST_STATE_SCROLL_HPP_INCLUDEGUARD

#include "Animation.hpp"
#include "GameState.hpp"
#include "Shape.hpp"
#include "Sprite.hpp"
#include "TweenAlpha.hpp"
#include <cstdint>
#include <iostream>
#include <vector>

class StateScroll : public jt::GameState {
private:
    jt::Shape::Sptr m_shape1;
    jt::Animation::Sptr m_anim;
    jt::Sprite::Sptr m_sprite;
    jt::Shape::Sptr m_background;

    void doInternalCreate() override;
    void doInternalUpdate(float const /*elapsed*/) override;
    void doInternalDraw() const override;
};

#endif
