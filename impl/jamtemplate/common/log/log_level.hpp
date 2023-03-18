#ifndef JAMTEMPLATE_LOG_LEVEL_HPP
#define JAMTEMPLATE_LOG_LEVEL_HPP

namespace jt {

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

} // namespace jt

#endif // JAMTEMPLATE_LOG_LEVEL_HPP
