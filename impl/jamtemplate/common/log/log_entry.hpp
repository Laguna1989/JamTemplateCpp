#ifndef JAMTEMPLATE_LOG_ENTRY_HPP
#define JAMTEMPLATE_LOG_ENTRY_HPP

#include <string>
#include <vector>

enum class LogLevel {
    LogLevelAction,
    LogLevelOff,
    LogLevelFatal,
    LogLevelError,
    LogLevelWarning,
    LogLevelInfo,
    LogLevelDebug,
    LogLevelVerbose
};

namespace jt {
/// POD type to represent one log entry
struct LogEntry {
    std::string message { "" };
    std::string time { "" };
    LogLevel level { LogLevel::LogLevelOff };
    std::vector<std::string> tags {};
};

} // namespace jt

#endif // JAMTEMPLATE_LOG_ENTRY_HPP
