#ifndef JAMTEMPLATE_LOG_ENTRY_HPP
#define JAMTEMPLATE_LOG_ENTRY_HPP

#include <log/log_level.hpp>
#include <string>
#include <vector>

namespace jt {

/// POD type to represent one log entry
struct LogEntry {
    std::string message { "" };
    std::string time { "" };
    LogLevel level { LogLevel::Off };
    std::vector<std::string> tags {};
};

} // namespace jt

#endif // JAMTEMPLATE_LOG_ENTRY_HPP
