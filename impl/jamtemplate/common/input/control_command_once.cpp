#include "control_command_once.hpp"

void jt::ControlCommandOnce::execute(float elapsed)
{
    if (!m_hasBeenExecutedAlready) {
        doExecute(elapsed);
        m_hasBeenExecutedAlready = true;
    }
}

void jt::ControlCommandOnce::reset() { m_hasBeenExecutedAlready = false; }
