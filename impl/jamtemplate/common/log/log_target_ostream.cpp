#include "log_target_ostream.hpp"
#include <log/log_entry.hpp>
#include <iostream>

jt::LogTargetOstream::LogTargetOstream(std::ostream& stream)
    : m_stream { stream }
{
}

void jt::LogTargetOstream::doLog(jt::LogEntry const& entry)
{
    m_stream << entry.message << std::endl;
}
