#include "log.hpp"

namespace jt {

void Log::verbose(std::string const& string)
{
    m_allLogs.emplace_back(LogEntry { string, "", LogLevel::LogLevelVerbose });
}

void Log::debug(std::string const& string)
{
    m_allLogs.emplace_back(LogEntry { string, "", LogLevel::LogLevelDebug });
}
void Log::error(std::string const& string)
{
    m_allLogs.emplace_back(LogEntry { string, "", LogLevel::LogLevelError });
}

void Log::clear() { m_allLogs.clear(); }

std::vector<jt::LogEntry> Log::getAllLogs() { return m_allLogs; }
} // namespace jt
