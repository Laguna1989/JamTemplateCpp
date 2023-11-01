#ifndef STRESSTEST_STATE_SCROLL_HPP
#define STRESSTEST_STATE_SCROLL_HPP

#include <animation.hpp>
#include <game_state.hpp>
#include <line.hpp>
#include <shape.hpp>
#include <sprite.hpp>
#include <text.hpp>

class StateMoveCam : public jt::GameState {
public:
    std::string getName() const override;

private:
    jt::Shape::Sptr m_shape1;
    jt::Shape::Sptr m_shape2;
    jt::Animation::Sptr m_anim;
    jt::Sprite::Sptr m_sprite;
    jt::Sprite::Sptr m_spriteDino;
    jt::Animation::Sptr m_animMiner;
    jt::Sprite::Sptr m_spriteCircle;
    jt::Shape::Sptr m_background;

    jt::Text::Sptr m_text_left_aligned;
    jt::Text::Sptr m_text_center_aligned;
    jt::Text::Sptr m_text_right_aligned;

    jt::Line::Sptr m_line1;
    jt::Line::Sptr m_line2;

    void onCreate() override;
    void onEnter() override;
    void onUpdate(float const /*elapsed*/) override;
    void onDraw() const override;
};

#endif
