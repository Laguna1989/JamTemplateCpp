#ifndef GUARD_JAMTEMPLATE_LOG_TARGET_INTERFACE_HPP
#define GUARD_JAMTEMPLATE_LOG_TARGET_INTERFACE_HPP

#include "log_entry.hpp"

namespace jt {
class LogTargetInterface {
public:
    virtual ~LogTargetInterface() = default;

    virtual void log(LogEntry const& entry) = 0;
    virtual void setLogLevel(LogLevel level) = 0;
};
} // namespace jt

#endif // GUARD_JAMTEMPLATE_LOG_TARGET_INTERFACE_HPP
