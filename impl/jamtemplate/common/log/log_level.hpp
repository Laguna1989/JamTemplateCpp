#ifndef JAMTEMPLATE_LOG_LEVEL_HPP
#define JAMTEMPLATE_LOG_LEVEL_HPP

namespace jt {

enum class LogLevel {
    // clang-format off
    Action,
    Off,
    Fatal,
    Error,
    Warning,
    Info,
    Debug,
    Verbose
    // clang-format on
};

} // namespace jt

#endif // JAMTEMPLATE_LOG_LEVEL_HPP
