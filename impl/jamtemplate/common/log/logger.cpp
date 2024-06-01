#include "logger.hpp"
#include <log/log_entry.hpp>
#include <log/log_target_interface.hpp>
#include <chrono>
#include <sstream>
#include <stdexcept>

void jt::Logger::action(std::string const& string, std::source_location source)
{
    addLogEntry(LogEntry { string, "", LogLevel::Action, {}, source });
}

void jt::Logger::fatal(
    std::string const& string, std::vector<std::string> const& tags, std::source_location source)
{
    if (m_logLevel >= LogLevel::Fatal) {
        addLogEntry(LogEntry { string, "", LogLevel::Fatal, tags, source });
    }
}

void jt::Logger::error(
    std::string const& string, std::vector<std::string> const& tags, std::source_location source)
{
    if (m_logLevel >= LogLevel::Error) {
        addLogEntry(LogEntry { string, "", LogLevel::Error, tags, source });
    }
}

void jt::Logger::warning(
    std::string const& string, std::vector<std::string> const& tags, std::source_location source)
{
    if (m_logLevel >= LogLevel::Warning) {
        addLogEntry(LogEntry { string, "", LogLevel::Warning, tags, source });
    }
}

void jt::Logger::info(
    std::string const& string, std::vector<std::string> const& tags, std::source_location source)
{
    if (m_logLevel >= LogLevel::Info) {
        addLogEntry(LogEntry { string, "", LogLevel::Info, tags, source });
    }
}

void jt::Logger::debug(
    std::string const& string, std::vector<std::string> const& tags, std::source_location source)
{
#ifdef JT_ENABLE_DEBUG
    if (m_logLevel >= LogLevel::Debug) {
        addLogEntry(LogEntry { string, "", LogLevel::Debug, tags, source });
    }
#endif
}

void jt::Logger::verbose(
    std::string const& string, std::vector<std::string> const& tags, std::source_location source)
{
#ifdef JT_ENABLE_DEBUG
    if (m_logLevel >= LogLevel::Verbose) {
        addLogEntry(LogEntry { string, "", LogLevel::Verbose, tags, source });
    }
#endif
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
}

void jt::Logger::setLogLevel(LogLevel level) { m_logLevel = level; }
