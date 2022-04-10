#include "log_target_cout.hpp"
#include <iostream>

void jt::LogTargetCout::log(jt::LogEntry const& entry)
{
    if (entry.level > m_logLevel) {
        return;
    }
    if (entry.level == LogLevel::LogLevelError) {
        std::cerr << entry.message << std::endl;
    } else {
        std::cout << entry.message << std::endl;
    }
}

void jt::LogTargetCout::setLogLevel(LogLevel level) { m_logLevel = level; }
