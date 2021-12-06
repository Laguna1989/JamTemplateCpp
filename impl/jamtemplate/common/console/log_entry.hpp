#ifndef GUARD_JAMTEMPLATE_LOG_ENTRY_HPP
#define GUARD_JAMTEMPLATE_LOG_ENTRY_HPP

#include <string>

enum class LogLevel { LogLevelVerbose, LogLevelDebug, LogLevelError };

namespace jt {
struct LogEntry {
    std::string message;
    std::string time;
    LogLevel level;
};
} // namespace jt

#endif // GUARD_JAMTEMPLATE_LOG_ENTRY_HPP
