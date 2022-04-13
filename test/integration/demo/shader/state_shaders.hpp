#ifndef JAMTEMPLATE_STATE_SHADERS_HPP
#define JAMTEMPLATE_STATE_SHADERS_HPP

#include <animation.hpp>
#include <game_state.hpp>
#include <line.hpp>
#include <shape.hpp>
#include <sprite.hpp>
#include <text.hpp>

class StateShaders : public jt::GameState {
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
    void doInternalUpdate(float elapsed) override;
    void doInternalDraw() const override;
};

#endif // JAMTEMPLATE_STATE_SHADERS_HPP
