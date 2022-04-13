#include "logger.hpp"
#include <chrono>
#include <sstream>
#include <stdexcept>

void jt::Logger::action(std::string const& string)
{
    addLogEntry(LogEntry { string, "", LogLevel::LogLevelAction, {} });
}

void jt::Logger::fatal(std::string const& string, std::vector<std::string> tags)
{
    if (m_logLevel >= LogLevel::LogLevelFatal) {
        addLogEntry(LogEntry { string, "", LogLevel::LogLevelFatal, tags });
    }
}

void jt::Logger::error(std::string const& string, std::vector<std::string> tags)
{
    if (m_logLevel >= LogLevel::LogLevelError) {
        addLogEntry(LogEntry { string, "", LogLevel::LogLevelError, tags });
    }
}

void jt::Logger::warning(std::string const& string, std::vector<std::string> tags)
{
    if (m_logLevel >= LogLevel::LogLevelWarning) {
        addLogEntry(LogEntry { string, "", LogLevel::LogLevelWarning, tags });
    }
}

void jt::Logger::info(std::string const& string, std::vector<std::string> tags)
{
    if (m_logLevel >= LogLevel::LogLevelInfo) {
        addLogEntry(LogEntry { string, "", LogLevel::LogLevelInfo, tags });
    }
}

void jt::Logger::debug(std::string const& string, std::vector<std::string> tags)
{
    if (m_logLevel >= LogLevel::LogLevelDebug) {
        addLogEntry(LogEntry { string, "", LogLevel::LogLevelDebug, tags });
    }
}

void jt::Logger::verbose(std::string const& string, std::vector<std::string> tags)
{
    if (m_logLevel >= LogLevel::LogLevelVerbose) {
        addLogEntry(LogEntry { string, "", LogLevel::LogLevelVerbose, tags });
    }
}

void jt::Logger::addLogTarget(std::shared_ptr<jt::LogTargetInterface> target)
{
    if (target == nullptr) {
        error("cannot add nullptr log target", { "jt" });
        return;
    }
    m_logTargets.push_back(target);
}

void jt::Logger::addLogEntry(jt::LogEntry entry)
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

std::vector<jt::LogEntry> const& jt::Logger::getHistory() { return m_history; }
void jt::Logger::setLogLevel(LogLevel level) { m_logLevel = level; }
void jt::Logger::clear() { m_history.clear(); }
