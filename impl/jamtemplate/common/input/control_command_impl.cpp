#include "control_command_impl.hpp"

namespace jt {

void ControlCommandImpl::execute(float elapsed)
{
    if (!m_hasBeenExecutedAlready) {
        doExecute(elapsed);
        m_hasBeenExecutedAlready = true;
    }
}

void ControlCommandImpl::reset() { m_hasBeenExecutedAlready = false; }

} // namespace jt