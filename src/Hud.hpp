﻿#ifndef GAME_HUD_HPP_INCLUDEGUARD
#define GAME_HUD_HPP_INCLUDEGUARD

#include "GameObject.hpp"
#include "SmartText.hpp"
#include <string>

class Hud : public jt::GameObject {
public:
    Hud();

    void AddScoreP1(int i = 1);
    void AddScoreP2(int i = 1);

private:
    int m_scoreP1 { -1 };
    int m_scoreP2 { -1 };

    jt::SmartText::Sptr m_scoreP1Text;
    jt::SmartText::Sptr m_scoreP2Text;

    void doUpdate(float const elapsed) override;

    void doDraw() const override;

    void doCreate() override;
};

#endif
