#ifndef GUARD_JAMTEMPLATE_LOG_INTERFACE_HPP
#define GUARD_JAMTEMPLATE_LOG_INTERFACE_HPP

#include "log_entry.hpp"
#include "log_target_interface.hpp"
#include <memory>
#include <string>
#include <vector>

namespace jt {
class LoggerInterface {
public:
    virtual ~LoggerInterface() = default;

    virtual void fatal(std::string const& string, std::vector<std::string> tags = {}) = 0;
    virtual void error(std::string const& string, std::vector<std::string> tags = {}) = 0;
    virtual void warning(std::string const& string, std::vector<std::string> tags = {}) = 0;
    virtual void info(std::string const& string, std::vector<std::string> tags = {}) = 0;
    virtual void debug(std::string const& string, std::vector<std::string> tags = {}) = 0;
    virtual void verbose(std::string const& string, std::vector<std::string> tags = {}) = 0;

    virtual void action(std::string const& string) = 0;

    virtual void addLogTarget(std::shared_ptr<LogTargetInterface> target) = 0;
    virtual std::vector<jt::LogEntry> const& getHistory() = 0;
    virtual void clear() = 0;

    virtual void setLogLevel(LogLevel level) = 0;
};
} // namespace jt

#endif // GUARD_JAMTEMPLATE_LOG_INTERFACE_HPP
