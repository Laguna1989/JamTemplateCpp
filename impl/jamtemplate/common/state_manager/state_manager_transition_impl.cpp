#include "state_manager_transition_impl.hpp"
#include <algorithm>

jt::StateManagerTransitionImpl::StateManagerTransitionImpl(float timerMax)
{
    m_timerMax = timerMax;
}

void jt::StateManagerTransitionImpl::start()
{
    m_timer = 0.0f;
    m_started = true;
    m_firstHalf = true;
    m_triggerStateChange = false;
    m_isInProgress = true;
}

bool jt::StateManagerTransitionImpl::isInProgress() { return m_isInProgress; }

bool jt::StateManagerTransitionImpl::triggerStateChange() { return m_triggerStateChange; }

void jt::StateManagerTransitionImpl::update(float elapsed)
{
    if (m_started) {
        if (m_firstHalf) {
            if (m_timer + elapsed >= m_timerMax) {
                m_triggerStateChange = true;
                m_firstHalf = false;
            }
            m_timer += elapsed;
            doUpdate(0);
        } else {

            m_timer -= elapsed;
            if (m_timer <= 0) {
                m_isInProgress = false;
                m_started = false;
            }
            doUpdate(0);
        }
    }
}

void jt::StateManagerTransitionImpl::draw(std::shared_ptr<jt::RenderTargetInterface> rt)
{
    if (m_started) {
        doDraw(rt);
    }
}

float jt::StateManagerTransitionImpl::getRatio() const
{
    float const ratio { m_timer / m_timerMax };
    return std::clamp(ratio, 0.0f, 1.0f);
}

bool jt::StateManagerTransitionImpl::isInFirstHalf() const { return m_firstHalf; }
