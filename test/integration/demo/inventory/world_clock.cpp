
#include "world_clock.hpp"
#include <drawable_helpers.hpp>
#include <game_interface.hpp>
#include <math_helper.hpp>
void WorldClock::doCreate()
{
    m_text = jt::dh::createText(renderTarget(), "00:00", 16);
    m_text->setZ(5);
    m_text->setIgnoreCamMovement(true);
    m_text->setTextAlign(jt::Text::TextAlign::LEFT);
    m_text->setPosition(jt::Vector2f { 5.0f, 0.0f });
}
void WorldClock::doUpdate(float const elapsed)
{
    if (getGame()->input().keyboard()->justPressed(jt::KeyCode::PageUp)) {
        m_factor *= 2.0f;
        if (m_factor >= 8.0f) {
            m_factor = 8.0f;
        }
    }
    if (getGame()->input().keyboard()->justPressed(jt::KeyCode::PageDown)) {
        m_factor /= 2.0f;
        if (m_factor <= 0.5f) {
            m_factor = 0.5f;
        }
    }
    m_text->update(elapsed);
    updateTime(elapsed);
    updateText();
}
void WorldClock::updateText()
{
    std::string minuteString = std::to_string(15 * m_quarter);
    if (minuteString.size() == 1) {
        minuteString = "00";
    }
    std::string hourString = std::to_string(m_hour);
    if (hourString.size() == 1) {
        hourString = "0" + hourString;
    }

    m_text->setText(hourString + ":" + minuteString + "  x"
        + jt::MathHelper::floatToStringWithXDecimalDigits(m_factor, 1));
}
void WorldClock::updateTime(float const elapsed)
{
    m_time += elapsed * m_factor;
    if (m_time >= m_timeToAdvanceInSeconds) {
        m_time -= m_timeToAdvanceInSeconds;
        m_quarter++;
        if (m_quarter >= 4) {
            m_quarter = 0;
            m_hour++;
            if (m_hour >= 24) {
                m_hour = 0;
                m_day++;
            }
        }
    }
}
void WorldClock::doDraw() const { m_text->draw(renderTarget()); }
