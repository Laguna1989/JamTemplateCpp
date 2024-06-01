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
    void action(
        std::string const& string, std::source_location = std::source_location::current()) override;
    void fatal(std::string const& string, std::vector<std::string> const& tags = {},
        std::source_location = std::source_location::current()) override;
    void error(std::string const& string, std::vector<std::string> const& tags = {},
        std::source_location = std::source_location::current()) override;
    void warning(std::string const& string, std::vector<std::string> const& tags = {},
        std::source_location = std::source_location::current()) override;
    void info(std::string const& string, std::vector<std::string> const& tags = {},
        std::source_location = std::source_location::current()) override;
    void debug(std::string const& string, std::vector<std::string> const& tags = {},
        std::source_location = std::source_location::current()) override;
    void verbose(std::string const& string, std::vector<std::string> const& tags = {},
        std::source_location = std::source_location::current()) override;

    void addLogTarget(std::shared_ptr<LogTargetInterface> target) override;
    void setLogLevel(LogLevel level) override;

private:
    std::vector<std::shared_ptr<jt::LogTargetInterface>> m_logTargets;

    void addLogEntry(LogEntry entry);
    LogLevel m_logLevel { LogLevel::Verbose };
};
} // namespace jt

#endif // JAMTEMPLATE_LOG_HPP
