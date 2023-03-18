#ifndef JAMTEMPLATE_LOG_HPP
#define JAMTEMPLATE_LOG_HPP

#include <log/log_entry.hpp>
#include <log/logger_interface.hpp>
#include <vector>

namespace jt {
class LogHistoryInterface;
class LogTargetInterface;

class Logger : public jt::LoggerInterface {
public:
    Logger(
        std::weak_ptr<jt::LogHistoryInterface> history = std::weak_ptr<jt::LogHistoryInterface> {});

    void action(std::string const& string) override;
    void fatal(std::string const& string, std::vector<std::string> const& tags = {}) override;
    void error(std::string const& string, std::vector<std::string> const& tags = {}) override;
    void warning(std::string const& string, std::vector<std::string> const& tags = {}) override;
    void info(std::string const& string, std::vector<std::string> const& tags = {}) override;
    void debug(std::string const& string, std::vector<std::string> const& tags = {}) override;
    void verbose(std::string const& string, std::vector<std::string> const& tags = {}) override;

    void addLogTarget(std::shared_ptr<LogTargetInterface> target) override;
    void setLogLevel(LogLevel level) override;

private:
    std::vector<std::shared_ptr<jt::LogTargetInterface>> m_logTargets;
    std::weak_ptr<jt::LogHistoryInterface> m_history;

    void addLogEntry(LogEntry entry);
    LogLevel m_logLevel { LogLevel::LogLevelVerbose };
    void addLogEntryToHistory(LogEntry const& entry) const;
};
} // namespace jt

#endif // JAMTEMPLATE_LOG_HPP
