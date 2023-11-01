#include "score_display.hpp"

ScoreDisplay::ScoreDisplay(
    jt::Text::Sptr text, std::string const& prefix, std::string const& postfix)
    : m_scoreText { text }
    , m_textPrefix { prefix }
    , m_textPostfix { postfix }
{
}

void ScoreDisplay::notify(int value)
{
    if (value >= 0) {
        m_scoreText->setText(m_textPrefix + std::to_string(value) + m_textPostfix);
        m_scoreText->update(0.0f);
    }
}
