#include "state_manager_transition_none.hpp"

namespace jt {

void StateManagerTransitionNone::start() { m_triggerdStateChange = false; }
bool StateManagerTransitionNone::isInProgress() { return false; }
void StateManagerTransitionNone::update(float /*elapsed*/) { }
void StateManagerTransitionNone::draw(std::shared_ptr<RenderTarget> /*rt*/) { }
bool StateManagerTransitionNone::triggerStateChange() { return true; }

} // namespace jt
