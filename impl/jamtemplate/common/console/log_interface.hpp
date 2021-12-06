#ifndef GUARD_JAMTEMPLATE_LOG_INTERFACE_HPP
#define GUARD_JAMTEMPLATE_LOG_INTERFACE_HPP

#include "log_entry.hpp"
#include <string>
#include <vector>

namespace jt {
class LogInterface {
public:
    virtual ~LogInterface() = default;

    virtual void debug(std::string const&) = 0;
    virtual void verbose(std::string const&) = 0;
    virtual void error(std::string const&) = 0;

    virtual void clear() = 0;

    virtual std::vector<jt::LogEntry> getAllLogs() = 0;
};
} // namespace jt

#endif // GUARD_JAMTEMPLATE_LOG_INTERFACE_HPP
