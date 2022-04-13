﻿#ifndef SCORE_DISPLAY_HPP
#define SCORE_DISPLAY_HPP

#include <hud/observer_interface.hpp>
#include <text.hpp>

class ScoreDisplay : public ObserverInterface<int> {
public:
    explicit ScoreDisplay(jt::Text::Sptr text, std::string const& prefix);
    void notify(int value) override;

private:
    jt::Text::Sptr const m_scoreText;
    std::string m_textPrefix;
};

#endif // !SCORE_DISPLAY_HPP
