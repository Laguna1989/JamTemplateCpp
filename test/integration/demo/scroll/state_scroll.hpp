#ifndef STRESSTEST_STATE_SCROLL_HPP_INCLUDEGUARD
#define STRESSTEST_STATE_SCROLL_HPP_INCLUDEGUARD

#include "animation.hpp"
#include "game_state.hpp"
#include "line.hpp"
#include "shape.hpp"
#include "sprite.hpp"
#include "text.hpp"

class StateScroll : public jt::GameState {
public:
    std::string getName() const override;

private:
    jt::Shape::Sptr m_shape1;
    jt::Animation::Sptr m_anim;
    jt::Sprite::Sptr m_sprite;
    jt::Shape::Sptr m_background;

    jt::Text::Sptr m_text_left_aligned;
    jt::Text::Sptr m_text_center_aligned;
    jt::Text::Sptr m_text_right_aligned;

    jt::Line::Sptr m_line;

    void doInternalCreate() override;
    void doInternalUpdate(float const /*elapsed*/) override;
    void doInternalDraw() const override;
};

#endif
