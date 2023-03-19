
#include "flicker_impl.hpp"
void jt::FlickerImpl::updateFlicker(float elapsed)
{
    m_flickerTimer -= elapsed;
    if (m_flickerTimer > 0) {
        m_flickerIntervalTimer -= elapsed;
        if (m_flickerIntervalTimer <= 0) {
            m_flickerIntervalTimer += m_flickerInterval;
            m_doDraw = !m_doDraw;
        }
    }
}
bool jt::FlickerImpl::allowDrawFromFlicker() const
{
    if (m_flickerTimer <= 0) {
        return true;
    }
    return m_doDraw;
}

void jt::FlickerImpl::doFlicker(float duration, float interval)
{
    m_flickerTimer = duration;
    m_flickerInterval = interval;
    m_flickerIntervalTimer = 0.0f;
}
