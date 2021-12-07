#ifndef GUARD_JAMTEMPLATE_LOG_ENTRY_HPP
#define GUARD_JAMTEMPLATE_LOG_ENTRY_HPP

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
struct LogEntry {
    std::string message { "" };
    std::string time { "" };
    LogLevel level { LogLevel::LogLevelOff };
    std::vector<std::string> tags {};
};

} // namespace jt

#endif // GUARD_JAMTEMPLATE_LOG_ENTRY_HPP
