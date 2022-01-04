#include "state_manager_transition_none.hpp"

namespace jt {

void StateManagerTransitionNone::start() { m_triggerdStateChange = false; }
bool StateManagerTransitionNone::isInProgress() { return false; }
void StateManagerTransitionNone::update(float /*elapsed*/) { }
void StateManagerTransitionNone::draw(std::shared_ptr<RenderTarget> /*rt*/) { }
void StateManagerTransitionNone::reset() { m_triggerdStateChange = false; }
bool StateManagerTransitionNone::triggerStateChange()
{
    if (!m_triggerdStateChange) {
        m_triggerdStateChange = true;
        return true;
    }
    return false;
}

} // namespace jt
