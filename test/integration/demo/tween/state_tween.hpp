#ifndef STRESSTEST_STATE_TWEEN_HPP
#define STRESSTEST_STATE_TWEEN_HPP

#include "game_state.hpp"
#include "shape.hpp"

class StateTween : public jt::GameState {
public:
    std::string getName() const override;
    void createTweens();

private:
    jt::Shape::Sptr m_overlayR;
    jt::Shape::Sptr m_overlayG;
    jt::Shape::Sptr m_overlayB;
    jt::Shape::Sptr m_background;

    void createRects();

    void onCreate() override;
    void onEnter() override;
    void onUpdate(float const /*elapsed*/) override;
    void onDraw() const override;
};

#endif
