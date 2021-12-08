#include "log_target_file.hpp"
jt::LogTargetFile::LogTargetFile() { m_file = std::ofstream { "log.txt" }; }
void jt::LogTargetFile::log(jt::LogEntry const& entry)
{
    if (entry.level > m_logLevel) {
        return;
    }
    m_file << entry.time << ": " << entry.message << std::endl;
}
void jt::LogTargetFile::setLogLevel(LogLevel level) { m_logLevel = level; }
