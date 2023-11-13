#include "log_target_base.hpp"
#include <log/log_entry.hpp>

namespace jt {
void LogTargetBase::log(LogEntry const& entry)
{
    if (entry.level > m_logLevel) {
        return;
    }
    doLog(entry);
}

void LogTargetBase::setLogLevel(LogLevel level) { m_logLevel = level; }

LogLevel LogTargetBase::getLogLevel() const { return m_logLevel; }

} // namespace jt
