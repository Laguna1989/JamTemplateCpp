#pragma once

#include <log/log_level.hpp>

namespace jt {

struct LogEntry;

class LogTargetInterface {
public:
    /// Log a log entry to the log target
    /// \param entry the entry to be logged
    virtual void log(LogEntry const& entry) = 0;

    /// Set the log level of this LogTarget
    /// \param level the loglevel
    virtual void setLogLevel(LogLevel level) = 0;

    /// Destructor
    virtual ~LogTargetInterface() = default;

    // no copy, no move. Avoid slicing.
    LogTargetInterface(LogTargetInterface const&) = delete;
    LogTargetInterface(LogTargetInterface&&) = delete;
    LogTargetInterface& operator=(LogTargetInterface const&) = delete;
    LogTargetInterface& operator=(LogTargetInterface&&) = delete;

protected:
    // default constructor can only be called from derived classes
    LogTargetInterface() = default;
};
} // namespace jt
