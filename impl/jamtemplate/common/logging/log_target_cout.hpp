#ifndef GUARD_JAMTEMPLATE_LOG_TARGET_COUT_HPP
#define GUARD_JAMTEMPLATE_LOG_TARGET_COUT_HPP

#include "log_target_interface.hpp"

namespace jt {
class LogTargetCout : public LogTargetInterface {
public:
    void setLogLevel(LogLevel level) override;
    void log(LogEntry const& entry) override;

private:
    LogLevel m_logLevel { LogLevel::LogLevelDebug };
};
} // namespace jt

#endif // GUARD_JAMTEMPLATE_LOG_TARGET_COUT_HPP
