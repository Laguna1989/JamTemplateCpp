#ifndef JAMTEMPLATE_LOG_INTERFACE_HPP
#define JAMTEMPLATE_LOG_INTERFACE_HPP

#include <log/log_level.hpp>
#include <memory>
#include <string>
#include <vector>

namespace jt {

class LogTargetInterface;

class LoggerInterface {
public:
    /// Log a fatal message
    /// \param string the log message
    /// \param tags the message tags
    virtual void fatal(std::string const& string, std::vector<std::string> const& tags = {})
        = 0;

    /// Log a error message
    /// \param string the log message
    /// \param tags the message tags
    virtual void error(std::string const& string, std::vector<std::string> const& tags = {})
        = 0;

    /// Log a warning message
    /// \param string the log message
    /// \param tags the message tags
    virtual void warning(std::string const& string, std::vector<std::string> const& tags = {})
        = 0;

    /// Log a info message
    /// \param string the log message
    /// \param tags the message tags
    virtual void info(std::string const& string, std::vector<std::string> const& tags = {})
        = 0;

    /// Log a debug message
    /// \param string the log message
    /// \param tags the message tags
    virtual void debug(std::string const& string, std::vector<std::string> const& tags = {})
        = 0;

    /// Log a verbose message
    /// \param string the log message
    /// \param tags the message tags
    virtual void verbose(std::string const& string, std::vector<std::string> const& tags = {})
        = 0;

    /// Log a action message (from the console
    /// \param string the log message
    /// \param tags the message tags
    virtual void action(
        std::string const& string)
        = 0;

    /// Add a log target to the logger
    /// \param target the target to be added
    virtual void addLogTarget(std::shared_ptr<LogTargetInterface> target) = 0;

    /// Set the overall log level
    virtual void setLogLevel(jt::LogLevel level) = 0;

    /// Destructor
    virtual ~LoggerInterface() = default;

    // no copy, no move. Avoid slicing.
    LoggerInterface(LoggerInterface const&) = delete;
    LoggerInterface(LoggerInterface&&) = delete;
    LoggerInterface& operator=(LoggerInterface const&) = delete;
    LoggerInterface& operator=(LoggerInterface&&) = delete;

protected:
    // default constructor can only be called from derived classes
    LoggerInterface() = default;
};
} // namespace jt

#endif // JAMTEMPLATE_LOG_INTERFACE_HPP
