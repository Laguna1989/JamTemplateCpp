#ifndef JAMTEMPLATE_LOG_HPP
#define JAMTEMPLATE_LOG_HPP

#include <log/log_entry.hpp>
#include <log/logger_interface.hpp>
#include <vector>

namespace jt {
class Logger : public jt::LoggerInterface {
public:
    void action(std::string const& string) override;
    void fatal(std::string const& string, std::vector<std::string> tags = {}) override;
    void error(std::string const& string, std::vector<std::string> tags = {}) override;
    void warning(std::string const& string, std::vector<std::string> tags = {}) override;
    void info(std::string const& string, std::vector<std::string> tags = {}) override;
    void debug(std::string const& string, std::vector<std::string> tags = {}) override;
    void verbose(std::string const& string, std::vector<std::string> tags = {}) override;

    void addLogTarget(std::shared_ptr<LogTargetInterface> target) override;
    void setLogLevel(LogLevel level) override;

    std::vector<jt::LogEntry> const& getHistory() override;
    void clear() override;

private:
    std::vector<std::shared_ptr<jt::LogTargetInterface>> m_logTargets;

    // TODO does the logger need to know about the history? Could be solved via decorator or
    // separate log_target
    std::vector<LogEntry> m_history;

    void addLogEntry(LogEntry entry);
    LogLevel m_logLevel { LogLevel::LogLevelVerbose };
};
} // namespace jt

#endif // JAMTEMPLATE_LOG_HPP
