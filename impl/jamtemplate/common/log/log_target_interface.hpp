#ifndef JAMTEMPLATE_LOG_TARGET_INTERFACE_HPP
#define JAMTEMPLATE_LOG_TARGET_INTERFACE_HPP

#include <log/log_entry.hpp>

namespace jt {
class LogTargetInterface {
public:
    virtual ~LogTargetInterface() = default;

    /// Log a log entry to the log target
    /// \param entry the entry to be logged
    virtual void log(LogEntry const& entry) = 0;
    /// Set the log level of this LogTarget
    /// \param level the loglevel
    virtual void setLogLevel(LogLevel level) = 0;
};
} // namespace jt

#endif // JAMTEMPLATE_LOG_TARGET_INTERFACE_HPP
