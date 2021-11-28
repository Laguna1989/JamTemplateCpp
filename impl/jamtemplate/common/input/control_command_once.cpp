#include "control_command_once.hpp"

namespace jt {

void ControlCommandOnce::execute(float elapsed)
{
    if (!m_hasBeenExecutedAlready) {
        doExecute(elapsed);
        m_hasBeenExecutedAlready = true;
    }
}

void ControlCommandOnce::reset() { m_hasBeenExecutedAlready = false; }

} // namespace jt
