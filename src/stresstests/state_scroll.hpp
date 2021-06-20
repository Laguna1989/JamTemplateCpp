#ifndef STRESSTEST_STATE_SCROLL_HPP_INCLUDEGUARD
#define STRESSTEST_STATE_SCROLL_HPP_INCLUDEGUARD

#include "animation.hpp"
#include "game_state.hpp"
#include "shape.hpp"
#include "sprite.hpp"

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
