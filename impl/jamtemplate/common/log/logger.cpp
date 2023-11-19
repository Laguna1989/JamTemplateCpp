#include "logger.hpp"
#include <log/log_entry.hpp>
#include <log/log_history_interface.hpp>
#include <log/log_target_interface.hpp>
#include <system_helper.hpp>
#include <chrono>
#include <sstream>
#include <stdexcept>

jt::Logger::Logger(std::weak_ptr<jt::LogHistoryInterface> history) { m_history = history; }

void jt::Logger::action(std::string const& string)
{
    addLogEntry(LogEntry { string, "", LogLevel::Action, {} });
}

void jt::Logger::fatal(std::string const& string, std::vector<std::string> const& tags)
{
    if (m_logLevel >= LogLevel::Fatal) {
        addLogEntry(LogEntry { string, "", LogLevel::Fatal, tags });
    }
}

void jt::Logger::error(std::string const& string, std::vector<std::string> const& tags)
{
    if (m_logLevel >= LogLevel::Error) {
        addLogEntry(LogEntry { string, "", LogLevel::Error, tags });
    }
}

void jt::Logger::warning(std::string const& string, std::vector<std::string> const& tags)
{
    if (m_logLevel >= LogLevel::Warning) {
        addLogEntry(LogEntry { string, "", LogLevel::Warning, tags });
    }
}

void jt::Logger::info(std::string const& string, std::vector<std::string> const& tags)
{
    if (m_logLevel >= LogLevel::Info) {
        addLogEntry(LogEntry { string, "", LogLevel::Info, tags });
    }
}

void jt::Logger::debug(std::string const& string, std::vector<std::string> const& tags)
{
    if (m_logLevel >= LogLevel::Debug) {
        addLogEntry(LogEntry { string, "", LogLevel::Debug, tags });
    }
}

void jt::Logger::verbose(std::string const& string, std::vector<std::string> const& tags)
{
    if (m_logLevel >= LogLevel::Verbose) {
        addLogEntry(LogEntry { string, "", LogLevel::Verbose, tags });
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
    addLogEntryToHistory(entry);
}

void jt::Logger::addLogEntryToHistory(jt::LogEntry const& entry) const
{
    if (SystemHelper::is_uninitialized_weak_ptr(m_history)) {
        return;
    }
    if (m_history.expired()) {
        return;
    }
    auto const h = m_history.lock();
    if (h == nullptr) {
        return;
    }
    h->addEntry(entry);
}

void jt::Logger::setLogLevel(LogLevel level) { m_logLevel = level; }
