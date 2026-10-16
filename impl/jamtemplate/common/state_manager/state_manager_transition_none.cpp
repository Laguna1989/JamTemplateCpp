#include "state_manager_transition_none.hpp"

void jt::StateManagerTransitionNone::start() { m_triggerdStateChange = false; }
bool jt::StateManagerTransitionNone::isInProgress() { return false; }
void jt::StateManagerTransitionNone::update(float /*elapsed*/) { }
void jt::StateManagerTransitionNone::draw(jt::RenderTargetInterface& /*rt*/) { }
bool jt::StateManagerTransitionNone::triggerStateChange() { return true; }
