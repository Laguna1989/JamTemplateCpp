#include "state_manager_transition_fade_to_black.hpp"
#include "math_helper.hpp"
#include <iostream>

namespace jt {

StateManagerTransitionFadeToBlack::StateManagerTransitionFadeToBlack(
    Vector2f const& size, TextureManagerInterface& tm, float timerMax)
{
    m_timerMax = timerMax;
    m_shape = std::make_shared<jt::Shape>();
    m_shape->makeRect(size, tm);
    m_shape->setColor(jt::Color { 0, 0, 0, 0 });
    m_shape->setIgnoreCamMovement(true);
}

bool StateManagerTransitionFadeToBlack::isInProgress() { return m_isInProgress; }

void StateManagerTransitionFadeToBlack::update(float elapsed)
{
    if (m_started) {
        if (m_firstHalf) {
            if (m_timer + elapsed >= m_timerMax) {
                m_triggerStateChange = true;
                m_firstHalf = false;
            }
            m_timer += elapsed;

            float ratio { m_timer / m_timerMax };
            ratio = jt::MathHelper::clamp(ratio, 0.0f, 1.0f);

            std::cout << "firsthalf " << ratio << std::endl;

            std::uint8_t a { static_cast<std::uint8_t>(ratio * 255.0f) };
            jt::Color const col { 0, 0, 0, a };
            m_shape->setColor(col);
            m_shape->update(elapsed);
        } else {

            m_timer -= elapsed;
            if (m_timer <= 0) {
                m_isInProgress = false;
                m_started = false;
            }
            float ratio { (m_timer) / m_timerMax };
            std::cout << "secondhalf " << ratio << std::endl;
            ratio = jt::MathHelper::clamp(ratio, 0.0f, 1.0f);

            std::uint8_t a { static_cast<std::uint8_t>(ratio * 255.0f) };
            jt::Color const col { 0, 0, 0, a };
            m_shape->setColor(col);
            m_shape->update(elapsed);
        }
    }
}

void StateManagerTransitionFadeToBlack::draw(std::shared_ptr<RenderTarget> rt)
{
    if (m_started) {
        m_shape->draw(rt);
    }
}

void StateManagerTransitionFadeToBlack::reset() { }

void StateManagerTransitionFadeToBlack::start()
{
    std::cout << "\nstart\n";
    m_timer = 0.0f;
    m_shape->setColor(jt::Color { 0, 0, 0, 0 });
    m_started = true;
    m_firstHalf = true;
    m_triggerStateChange = false;
    m_isInProgress = true;
}

bool StateManagerTransitionFadeToBlack::triggerStateChange() { return m_triggerStateChange; }

} // namespace jt
