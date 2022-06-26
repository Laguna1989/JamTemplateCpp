#include "log_target_ostream.hpp"
#include <iostream>

jt::LogTargetOstream::LogTargetOstream(std::ostream& stream)
    : m_stream { stream }
{
}

void jt::LogTargetOstream::log(jt::LogEntry const& entry)
{
    if (entry.level > m_logLevel) {
        return;
    }
    m_stream << entry.message << std::endl;
}

void jt::LogTargetOstream::setLogLevel(LogLevel level) { m_logLevel = level; }
