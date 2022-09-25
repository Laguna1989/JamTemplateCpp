#ifndef JAMTEMPLATE_LOG_INTERFACE_HPP
#define JAMTEMPLATE_LOG_INTERFACE_HPP

#include <log/log_entry.hpp>
#include <log/log_target_interface.hpp>
#include <memory>
#include <string>
#include <vector>

namespace jt {
class LoggerInterface {
public:
    virtual ~LoggerInterface() = default;

    /// Log a fatal message
    /// \param string the log message
    /// \param tags the message tags
    virtual void fatal(std::string const& string, std::vector<std::string> tags = {}) = 0;

    /// Log a error message
    /// \param string the log message
    /// \param tags the message tags
    virtual void error(std::string const& string, std::vector<std::string> tags = {}) = 0;

    /// Log a warning message
    /// \param string the log message
    /// \param tags the message tags
    virtual void warning(std::string const& string, std::vector<std::string> tags = {}) = 0;

    /// Log a info message
    /// \param string the log message
    /// \param tags the message tags
    virtual void info(std::string const& string, std::vector<std::string> tags = {}) = 0;

    /// Log a debug message
    /// \param string the log message
    /// \param tags the message tags
    virtual void debug(std::string const& string, std::vector<std::string> tags = {}) = 0;

    /// Log a verbose message
    /// \param string the log message
    /// \param tags the message tags
    virtual void verbose(std::string const& string, std::vector<std::string> tags = {}) = 0;

    /// Log a action message (from the console
    /// \param string the log message
    /// \param tags the message tags
    virtual void action(std::string const& string) = 0;

    /// Add a log target to the logger
    /// \param target the target to be added
    virtual void addLogTarget(std::shared_ptr<LogTargetInterface> target) = 0;

    /// Get the history of log entries
    /// \return
    virtual std::vector<jt::LogEntry> const& getHistory() = 0;

    /// Clear all log entries
    virtual void clear() = 0;

    /// Set the overall log level
    virtual void setLogLevel(LogLevel level) = 0;
};
} // namespace jt

#endif // JAMTEMPLATE_LOG_INTERFACE_HPP
