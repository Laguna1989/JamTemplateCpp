#include "log_target_file.hpp"
#include <log/log_entry.hpp>

jt::LogTargetFile::LogTargetFile()
    : m_file { std::ofstream { "log.txt" } }
{
}

void jt::LogTargetFile::doLog(jt::LogEntry const& entry)
{
    std::string sourceText = std::string { entry.source.file_name() } + ":"
        + std::to_string(entry.source.line()) + " [" + entry.source.function_name() + "]";

    m_file << entry.time << ": " << entry.message << " " << sourceText << std::endl;
}
