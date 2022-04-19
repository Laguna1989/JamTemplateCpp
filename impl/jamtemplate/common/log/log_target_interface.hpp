#ifndef JAMTEMPLATE_LOG_TARGET_INTERFACE_HPP
#define JAMTEMPLATE_LOG_TARGET_INTERFACE_HPP

#include <log/log_entry.hpp>

namespace jt {
class LogTargetInterface {
public:
    virtual ~LogTargetInterface() = default;

    virtual void log(LogEntry const& entry) = 0;
    virtual void setLogLevel(LogLevel level) = 0;
};
} // namespace jt

#endif // JAMTEMPLATE_LOG_TARGET_INTERFACE_HPP
