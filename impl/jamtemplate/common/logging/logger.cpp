#include "logger.hpp"
#include <chrono>
#include <sstream>
#include <stdexcept>

namespace jt {

void Logger::action(std::string const& string)
{
    addLogEntry(LogEntry { string, "", LogLevel::LogLevelAction, {} });
}

void Logger::fatal(std::string const& string, std::vector<std::string> tags)
{
    if (m_logLevel >= LogLevel::LogLevelFatal) {
        addLogEntry(LogEntry { string, "", LogLevel::LogLevelFatal, tags });
    }
}

void Logger::error(std::string const& string, std::vector<std::string> tags)
{
    if (m_logLevel >= LogLevel::LogLevelError) {
        addLogEntry(LogEntry { string, "", LogLevel::LogLevelError, tags });
    }
}

void Logger::warning(std::string const& string, std::vector<std::string> tags)
{
    if (m_logLevel >= LogLevel::LogLevelWarning) {
        addLogEntry(LogEntry { string, "", LogLevel::LogLevelWarning, tags });
    }
}

void Logger::info(std::string const& string, std::vector<std::string> tags)
{
    if (m_logLevel >= LogLevel::LogLevelInfo) {
        addLogEntry(LogEntry { string, "", LogLevel::LogLevelInfo, tags });
    }
}

void Logger::debug(std::string const& string, std::vector<std::string> tags)
{
    if (m_logLevel >= LogLevel::LogLevelDebug) {
        addLogEntry(LogEntry { string, "", LogLevel::LogLevelDebug, tags });
    }
}

void Logger::verbose(std::string const& string, std::vector<std::string> tags)
{
    if (m_logLevel >= LogLevel::LogLevelVerbose) {
        addLogEntry(LogEntry { string, "", LogLevel::LogLevelVerbose, tags });
    }
}

void Logger::addLogTarget(std::shared_ptr<LogTargetInterface> target)
{
    if (target == nullptr) {
        error("cannot add nullptr log target", { "jt" });
        return;
    }
    m_logTargets.push_back(target);
}

void Logger::addLogEntry(LogEntry entry)
{
    std::stringstream ss;
    auto now = std::chrono::system_clock::now();
    ss << std::chrono::system_clock::to_time_t(now);
    entry.time = ss.str();
    for (auto& t : m_logTargets) {
        t->log(entry);
    }
    m_history.push_back(entry);
}
std::vector<jt::LogEntry> const& Logger::getHistory() { return m_history; }
void Logger::setLogLevel(LogLevel level) { m_logLevel = level; }
void Logger::clear() { m_history.clear(); }

} // namespace jt
