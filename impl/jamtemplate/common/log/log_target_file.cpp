#include "log_target_file.hpp"
#include <log/log_entry.hpp>

jt::LogTargetFile::LogTargetFile()
    : m_file { std::ofstream { "log.txt" } }
{
}

void jt::LogTargetFile::doLog(jt::LogEntry const& entry)
{
    m_file << entry.time << ": " << entry.message << std::endl;
}
