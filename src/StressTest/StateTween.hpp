#ifndef STRESSTEST_STATE_TWEEN_HPP_INCLUDEGUARD
#define STRESSTEST_STATE_TWEEN_HPP_INCLUDEGUARD

#include "GameState.hpp"
#include "Shape.hpp"
#include "TweenAlpha.hpp"
#include <cstdint>
#include <iostream>
#include <vector>

class StateTween : public jt::GameState {
private:
    jt::Shape::Sptr m_overlayR;
    jt::Shape::Sptr m_overlayG;
    jt::Shape::Sptr m_overlayB;
    jt::Shape::Sptr m_background;

    void createRects();
    void createTweens();
    void doInternalCreate() override;
    void doInternalUpdate(float const /*elapsed*/) override;
    void doInternalDraw() const override;
};

#endif
