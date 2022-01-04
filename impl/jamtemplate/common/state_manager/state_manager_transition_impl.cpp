#include "state_manager_transition_impl.hpp"
#include "math_helper.hpp"

namespace jt {

StateManagerTransitionImpl::StateManagerTransitionImpl(float timerMax) { m_timerMax = timerMax; }

void StateManagerTransitionImpl::start()
{
    m_timer = 0.0f;
    m_started = true;
    m_firstHalf = true;
    m_triggerStateChange = false;
    m_isInProgress = true;
}

bool StateManagerTransitionImpl::isInProgress() { return m_isInProgress; }

bool StateManagerTransitionImpl::triggerStateChange() { return m_triggerStateChange; }

void StateManagerTransitionImpl::update(float elapsed)
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

void StateManagerTransitionImpl::draw(std::shared_ptr<RenderTarget> rt)
{
    if (m_started) {
        doDraw(rt);
    }
}

float StateManagerTransitionImpl::getRatio() const
{
    float ratio { m_timer / m_timerMax };
    return jt::MathHelper::clamp(ratio, 0.0f, 1.0f);
}

bool StateManagerTransitionImpl::isInFirstHalf() const { return m_firstHalf; }

} // namespace jt
